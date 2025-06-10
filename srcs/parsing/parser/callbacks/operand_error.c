/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:51:01 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:59:21 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Handles the case where a left operand is required but not provided.
 *
 * @param args The lexer arguments containing the current parsing context.
 * @param token The current token to be checked.
 * 
 * @return COMMAND_VALID to go to the next check
*/
t_parse_status	err_miss_left_operand(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!get_prev_token(args, &prev_token)
		|| (
			!is_text_token(prev_token)
			&& !(prev_token->type & OP_PARENTHESIS_CLOSE)
		))
		return (print_error_message(token, "err_missing_left_operand"));
	return (COMMAND_VALID);
}

/**
 * @brief Handles the case where a left operand is unexpected.
 *
 * @param args The lexer arguments containing the current parsing context.
 * @param token The current token to be checked.
 * 
 * @return COMMAND_VALID to go to the next check
*/
t_parse_status	err_unexp_left_operand(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!(!get_prev_token(args, &prev_token)
			|| (
				!is_text_token(prev_token)
				&& !(prev_token->type & OP_PARENTHESIS_CLOSE)
			)))
		return (print_error_message(token, "err_no_left_operand"));
	return (COMMAND_VALID);
}
