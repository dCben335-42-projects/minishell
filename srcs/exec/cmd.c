/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:57:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/15 16:52:32 by abonneau         ###   ########.fr       */
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
	char 	*strs[2];

	tmp = readline(SHELL_NEXT_NAME);
	strs[0] = input;
	strs[1] = tmp;
	
	new_input = ft_strsjoin((const char **)strs, 2, " ");
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
	t_token				*token;

	token = ((t_token *)get_dynarray_value_last(&args->tokens));
	if (args->parenthesis.open > args->parenthesis.close && (is_text_token(*token) || token->type & OP_SEMICOL))
	{
		if (is_text_token(*token))
		{
			tmp = ft_strjoin(input, ";");
			if (!tmp)
			{
				printf("Error: %s\n", args->error);
				return ;
			}
			free(input);
			input = tmp;			
		}
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
	{
		add_history(input);
		return ;
	}
	if (*input)
		add_history(input);
}

int	command_handler(char *input, t_shell *shell)
{
	t_lexer_args	args;
	(void)shell;
	t_ast_node		*cmds;
	(void)cmds;

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
	print_tokens(&args.tokens);
	cmds = ast_builder(&args.tokens);
	if (!cmds)
	{
		destroy_lexer_args(&args);
		return (0);
	}
	//if (DEBUG_MODE)
	//{
	//	ft_printf("<--DEBUG_MODE-->\n");
	//	ft_printf("COMMAND: %s\n", input);
	//	ft_printf("ABSTRACT SYNTAX TREE:\n");
	//	print_ast_json_wrapper(cmds->content);
	//}
	//get_all_heredoc(cmds);
	if (DEBUG_MODE)
	{
		ft_printf("<--DEBUG_MODE-->\n");
		ft_printf("COMMAND: %s\n", input);
		ft_printf("ABSTRACT SYNTAX TREE:\n");
		print_ast_json_wrapper(cmds->content);
	}
	orchestrator(cmds->content);
	destroy_lexer_args(&args);
	destroy_dynarray(cmds->content);
	free(cmds);
	//expand(shell, &args.tokens);
	//destroy_lexer_args(&args);
	return (1);
}
