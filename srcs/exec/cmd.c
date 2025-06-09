/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:57:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 17:45:50 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct_ast.h"
#include "config.h"
#include "utils.h"
#include "minishell_signal.h"

void	*command_handler_lexer(char *input, t_lexer_args *args, t_dynarray *heredoc_cval);

static void	*command_not_finished(t_lexer_args *args, char *sep)
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
	return (command_handler_lexer(new_input, args, args->heredoc_cval));
}

void	*command_not_finished_handler(t_lexer_args *args)
{
	char				*tmp;
	t_token				*token;

	token = get_dynarray_last_value(&args->tokens);
	if (args->quote)
	{
		tmp = ft_strjoin(args->base_input, "\n");
		if (!tmp)
			return (NULL);
		free(args->base_input);
		args->base_input = tmp;	
		return (command_not_finished(args, ""));
	}
	if (args->parenthesis.open > args->parenthesis.close && (is_text_token(token) || token->type & OP_SEMICOL))
	{
		if (is_text_token(token))
		{
			tmp = ft_strjoin(args->base_input, ";");
			if (!tmp)
				return (NULL);
			free(args->base_input);
			args->base_input = tmp;		
		}
	}
	return (command_not_finished(args, " "));
}

void	*command_handler_lexer(char *input, t_lexer_args *args, t_dynarray *heredoc_cval)
{
	t_parse_status	status;
	
	if (!heredoc_cval)
		heredoc_cval = init_dynarray_malloc(3, (void *(*)(void *))free_value);
	if (!heredoc_cval->data)
		return (NULL);
	*args = init_lexer_args(input, heredoc_cval, TRUE);
	if (!args->tokens.data)
		return (NULL);
	status = lexer(args);
	if (args->interrupted)
		return (NULL);
	if (status == MALLOC_ERROR || status == COMMAND_NOT_VALID)
		return (NULL);
	if (status == COMMAND_NOT_FINISHED)
		return (command_not_finished_handler(args));
	return (args->tokens.data);
}


void	*command_handler(char *input, t_shell *shell)
{
	t_lexer_args	args;
	t_bool			is_lexer_error;
	
	is_lexer_error = !command_handler_lexer(input, &args, NULL);
	add_history(args.base_input);
	free(args.base_input);
	debug_tokens(shell, &args.tokens);
	if (is_lexer_error)
	{
		shell->exit_code = 2;
		if (args.interrupted)
			shell->exit_code = 130;
		return (destroy_lexer_args(&args, TRUE));
	}
	shell->ast = ast_builder(&args.tokens);
	destroy_lexer_args(&args, TRUE);
	if (!shell->ast)
		return (NULL);
	debug_ast(shell);
	orchestrator(shell);
	destroy_ast(shell->ast);
	shell->ast = NULL;
	return (shell);
}
