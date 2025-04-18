/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:57:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 19:13:41 by bcabocel         ###   ########.fr       */
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
		printf("Token: %-12s", data->value);
		printf(" | ");
		printf("Type: %s", get_token_type_name(data->type));
		printf("\n==================================");
		printf("==================================\n");
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
	if (!new_input)
	{
		printf("Error: %s\n", args->error);
		return ;
	}
	destroy_lexer_args(args);
	command_handler_lexer(new_input, args);
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
	{
		command_not_finished(args, input);
		return ;
	}
	if (status != COMMAND_VALID)
	{
		printf("Error: %s\n", args->error);
		return ;
	}
	print_tokens(&args->tokens);
	if (*input)
		add_history(input);
}

int	command_handler(char *input, t_shell *shell)
{
	t_lexer_args	args;

	command_handler_lexer(input, &args);
	if (args.tokens.count == 0)
	{
		destroy_lexer_args(&args);
		return (0);
	}
	expand(shell, &args.tokens);
	print_tokens(&args.tokens);
	destroy_lexer_args(&args);
	return (0);
}
