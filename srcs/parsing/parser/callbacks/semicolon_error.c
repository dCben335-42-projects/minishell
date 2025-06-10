/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:47:21 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 04:00:08 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Handles the case where a semicolon is expected but not provided.
 *
 * @param args The lexer arguments containing the current parsing context.
 * @param token The current token to be checked.
 * 
 * @return COMMAND_VALID if the semicolon is valid, otherwise prints 
 * an error message * and returns COMMAND_NOT_VALID.
 */
t_parse_status	err_empty_semicol(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!get_prev_token(args, &prev_token)
		|| (is_control_token(prev_token) && token->type & OP_SEMICOL))
		return (print_error_message(token, "err_empty_semicol"));
	return (COMMAND_VALID);
}
