/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_need.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:50:57 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:50:59 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Handles the case where a right operand is required but not provided.
 *
 * @param args The lexer arguments containing the current parsing context.
 * @param token The current token to be checked.
 * 
 * @note This function sets the `rhs` status to `REQUIRED`, 
 * indicating that a right operand is expected.
 * 
 * @return COMMAND_VALID to go to the next check
*/
t_parse_status	err_miss_right_operand(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->rhs = REQUIRED;
	return (COMMAND_VALID);
}

/**
 * 
 * @brief Handles the case where a right operand is disallowed.
 *
 * @param args The lexer arguments containing the current parsing context.
 * @param token The current token to be checked.
 * 
 * @note This function sets the `rhs` status to `DISALLOWED`, 
 * indicating that a right operand is not allowed in this context.
 * 
 * @return COMMAND_VALID to go to the next check
 * 
*/
t_parse_status	err_unexp_right_operand(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->rhs = DISALLOWED;
	return (COMMAND_VALID);
}

/**
 * 
 * @brief Handles the case where a right operand is required without parentheses.
 *
 * @param args The lexer arguments containing the current parsing context.
 * @param token The current token to be checked.
 * 
 * @note This function sets the `rhs` status to `REQUIRED_WITHOUT_PAREN`, 
 * indicating that a right operand is expected without parentheses.
 * 
 * @return COMMAND_VALID to go to the next check
*/
t_parse_status	err_miss_right_operand_np(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->rhs = REQUIRED_WITHOUT_PAREN;
	return (COMMAND_VALID);
}
