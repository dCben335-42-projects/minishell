/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:57:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 20:15:46 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast_node.h"

void	*command_handler_lexer(char *input, t_lexer_args *args);
// static void	print_tokens(t_dynarray *tokens)
// {
// 	t_uint	i;
// 	t_uint	count;
// 	t_token	*data;

// 	i = 0;
// 	count = tokens->count;
// 	while (i < count)
// 	{
// 		data = (t_token *)get_dynarray_value(tokens, i);
// 		printf("%-40s %-40s\n", get_token_type_name(data->type), data->value);
// 		i++;
// 	}
// }

static void	*command_not_finished(t_lexer_args *args)
{
	char	*new_input;
	char	*tmp;
	char 	*strs[2];

	tmp = readline(SHELL_NEXT_NAME);
	strs[0] = args->base_input;
	strs[1] = tmp;
	new_input = ft_strsjoin((const char **)strs, 2, " ");
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

	token = get_dynarray_value_last(&args->tokens);
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
	return (command_not_finished(args));
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
	if (args.base_input)
	{
		add_history(args.base_input);
		free(args.base_input);
	}
	if (is_lexer_error)
		return (destroy_lexer_args(&args));
	shell->ast = ast_builder(&args.tokens);
	destroy_lexer_args(&args);
	if (!shell->ast)
		return (0);
	if (DEBUG_MODE)
	{
		printf("<--DEBUG_MODE-->\n");
		printf("ABSTRACT SYNTAX TREE:\n");
		print_ast_json_wrapper(shell->ast->content);
	}
	orchestrator(shell);
	recursive_destroy_node(shell->ast);
	shell->ast = NULL;
	return (shell);
}
