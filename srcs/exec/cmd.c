/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:57:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 07:34:13 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast_node.h"
#include "utils.h"

void	*command_handler_lexer(char *input, t_lexer_args *args);

static void	*command_not_finished(t_lexer_args *args, char *sep)
{
	char	*new_input;
	char	*tmp;

	tmp = readline(args->not_finished_value);
	if (!tmp)
		return (NULL);
	new_input = ft_strsjoin((const char *[]){args->base_input, tmp}, 2, sep);
	free(tmp);
	free(args->base_input);
	if (!new_input)
		return (NULL);
	destroy_lexer_args(args);
	return (command_handler_lexer(new_input, args));
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
	if (args->parenthesis.open > args->parenthesis.close && (is_text_token(*token) || token->type & OP_SEMICOL))
	{
		if (is_text_token(*token))
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

void	*command_handler_lexer(char *input, t_lexer_args *args)
{
	t_parse_status	status;

	*args = init_lexer_args(input);
	if (!args->tokens.data)
		return (NULL);
	status = lexer(args);
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
	
	is_lexer_error = !command_handler_lexer(input, &args);
	add_history(args.base_input);
	free(args.base_input);
	if (is_lexer_error)
	{
		shell->exit_code = 2;
		return (destroy_lexer_args(&args));
	}
	debug_tokens(shell, &args.tokens);
	shell->ast = ast_builder(&args.tokens);
	destroy_lexer_args(&args);
	if (!shell->ast)
		return (NULL);
	debug_ast(shell);
	orchestrator(shell);
	recursive_destroy_node(shell->ast);
	shell->ast = NULL;
	return (shell);
}
