/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:57:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 23:50:49 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_ast.h"
#include "parsing.h"
#include "config.h"
#include "utils.h"
#include "minishell_signal.h"
#include <readline/readline.h>

void	*process_prompt(t_lexer_args *args, t_dynarray *heredoc_cval, const char *prompt);

static void	*prompt_recall(t_lexer_args *args, const char *sep)
{
	const int	saved_stdin = dup(STDIN_FILENO);
	char		*new_input;
	char		*tmp;

	signals(SIGCTX_HEREDOC);
	tmp = readline(args->not_finished_value);
	restore_std_in_out(saved_stdin, -1);
	signals(SIGCTX_SHELL);
	if (!tmp && !g_sig)
		ft_putendl_fd(ERR_SYNTAX_EOF, 2);
	else if (!tmp && g_sig)
	{
		args->interrupted = TRUE;
		g_sig = 0;
	}
	if (!tmp)
		return (NULL);
	new_input = ft_strsjoin((const char *[]){args->base_input, tmp}, 2, sep);
	free(tmp);
	free(args->base_input);
	if (!new_input)
		return (NULL);
	destroy_lexer_args(args, FALSE);
	return (process_prompt(args, args->heredoc_cval, new_input));
}

static void *join_base_input(t_lexer_args *args, const char *str)
{
	char	*tmp;

	tmp = ft_strjoin(args->base_input, str);
	if (!tmp)
		return (NULL);
	free(args->base_input);
	args->base_input = tmp;
	return (args->base_input);
}

static void	*prompt_not_finished(t_lexer_args *args)
{
	t_token		*token;
	const char	*sep;

	token = get_dynarray_last_value(&args->tokens);
	sep = " ";
	if (args->quote)
	{
		args->base_input = join_base_input(args, "\n");
		sep = "";
	}
	if (args->parenthesis.open > args->parenthesis.close && is_text_token(token))
		args->base_input = join_base_input(args, ";");
	if (!args->base_input)
		return (NULL);
	return (prompt_recall(args, sep));
}

void	*process_prompt(t_lexer_args *args, t_dynarray *heredoc_cval, const char *prompt)
{
	t_parse_status	status;
	
	if (!heredoc_cval)
		heredoc_cval = init_dynarray_malloc(3, (void *(*)(void *))free_value);
	*args = init_lexer_args(prompt, heredoc_cval);
	if (!args->tokens.data || !heredoc_cval->data)
		return (NULL);
	status = lexer(args);
	if (args->interrupted)
		return (NULL);
	if (status == MALLOC_ERROR || status == COMMAND_NOT_VALID)
		return (NULL);
	if (status == COMMAND_NOT_FINISHED)
		return (prompt_not_finished(args));
	return (args->tokens.data);
}
