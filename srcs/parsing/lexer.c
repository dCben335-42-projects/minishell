/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:18:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/16 19:05:52 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	is_command_finished(
	t_lexer_args *args,
	t_token *token,
	const char *input
)
{
	if (token->rules & EXPECT_CONT
		|| args->parenthesis.open > args->parenthesis.close)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
		{
			args->not_finished_value = get_readline_arg(token->type);
			return (FALSE);
		}
	}
	return (TRUE);
}

t_parse_status	get_parsing_error_status(t_lexer_args *args, t_ptr ptr)
{
	t_parse_status	status;

	if (ptr.has_malloc_error)
		return (MALLOC_ERROR);
	status = token_parser(args, ptr.p);
	if (status != COMMAND_VALID)
		return (status);
	if (!is_command_finished(args, ptr.p, args->input))
		return (COMMAND_NOT_FINISHED);
	return (status);
}

/**
 * @brief Analyzes the input to determine if it follows a valid command format.
 *
 * This function processes the input string using lexical analysis 
 * to extract tokens and validate the command structure.
 *
 * @param args The lexer arguments containing the input string and 
 * parsing context.
 * @return The status of the command parsing:
 * - `COMMAND_VALID` if the command is correctly formatted.
 * - `COMMAND_NOT_VALID` if the command contains syntax errors.
 * - `COMMAND_NOT_FINISHED` if the command is incomplete
 * (e.g., missing closing quotes).
 */
t_parse_status	lexer(t_lexer_args *args)
{
	t_parse_status	status;
	t_ptr			ptr;

	ptr = get_next_token(args);
	while (ptr.p)
	{
		status = get_parsing_error_status(args, ptr);
		if (status != COMMAND_VALID)
			return (status);
		if (args->is_heredoc)
			ptr = transform_heredoc(args);
		else
			ptr = get_next_token(args);
	}
	if (ptr.has_malloc_error)
		return (MALLOC_ERROR);
	ptr = init_pointer(init_token(M_EOF, "newline", 7), TRUE);
	if (ptr.has_malloc_error)
		return (MALLOC_ERROR);
	return (token_parser(args, ptr.p));
}
