/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:57:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/07 15:35:23 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_handler_lexer(char *input, t_lexer_args *args);

static void	print_tokens(t_dynarray *tokens)
{
	t_uint	i;
	t_uint	count;
	t_token	*data;

	i = 0;
	count = tokens->count;
	while (i < count)
	{
		data = (t_token *)get_dynarray_value(tokens, i);
		printf("%-40s %-40s\n", get_token_type_name(data->type), data->value);
		i++;
	}
}

static void	command_not_finished(t_lexer_args *args, char *input)
{
	char	*new_input;
	char	*tmp;

	tmp = readline(SHELL_NEXT_NAME);
	new_input = ft_strjoin(input, tmp);
	free(tmp);
	free(input);
	if (!new_input)
	{
		printf("Error: %s\n", args->error);
		return ;
	}
	destroy_lexer_args(args);
	command_handler_lexer(new_input, args);
}

void	command_not_finished_handler(t_lexer_args *args, char *input)
{
	char				*tmp;
	t_token_type_flags	token_type;

	token_type = ((t_token *)get_dynarray_value_last(&args->tokens))->type;
	if (args->parenthesis.open > args->parenthesis.close && (token_type & (E_TOKEN_NAME_MASK | OP_SEMICOL)))
	{
		if (token_type & OP_SEMICOL)
			tmp = ft_strjoin(input, " ");
		else
			tmp = ft_strjoin(input, "; ");
		if (!tmp)
		{
			printf("Error: %s\n", args->error);
			return ;
		}
		free(input);
		input = tmp;
	}
	command_not_finished(args, input);
	return ;
}

void	command_handler_lexer(char *input, t_lexer_args *args)
{
	t_parse_status	status;

	*args = init_lexer_args(input);
	if (!args->tokens.data)
	{
		printf("Error: %s\n", args->error);
		return ;
	}
	status = lexer(args);
	if (status == COMMAND_NOT_FINISHED)
		return (command_not_finished_handler(args, input));
	if (status != COMMAND_VALID)
		return ;
	if (*input)
		add_history(input);
}

int	command_handler(char *input, t_shell *shell)
{
	t_lexer_args	args;
	t_ast_node		*cmds;

	command_handler_lexer(input, &args);
	if (args.error)
	{
		printf("Error: %s\n", args.error);
		destroy_lexer_args(&args);
		return (0);
	}
	if (args.tokens.count == 0)
	{
		destroy_lexer_args(&args);
		return (0);
	}
	cmds = ast_builder(&args.tokens);
	destroy_lexer_args(&args);
	shell->ast = cmds;
	if (!cmds)
		return (0);
	if (DEBUG_MODE)
	{
		ft_printf("<--DEBUG_MODE-->\n");
		ft_printf("COMMAND: %s\n", input);
		ft_printf("ABSTRACT SYNTAX TREE:\n");
		print_tokens(&args.tokens);
		print_ast_json_wrapper(cmds->content);
	}
	orchestrator(shell);
	destroy_dynarray(cmds->content);
	free(cmds);
	shell->ast = NULL;
	//expand(shell, &args.tokens);
	//destroy_lexer_args(&args);
	return (1);
}
