/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:47:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:56:45 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * 
 * @brief Increments the count of open parentheses in the lexer arguments.
 *
 * @param args The lexer arguments containing the current parsing context.
 * @param token The current token to be checked (not used in this function).
 *
 * @return COMMAND_VALID to indicate that the command is valid and to proceed.
 * 
 */
t_parse_status	inc_parenthesis_open(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->parenthesis.open++;
	return (COMMAND_VALID);
}

/**
 * 
 * @brief Increments the count of close parentheses in the lexer arguments.
 *
 * @param args The lexer arguments containing the current parsing context.
 * @param token The current token to be checked (not used in this function).
 *
 * @return COMMAND_VALID to indicate that the command is valid and to proceed.
 * 
 */
t_parse_status	inc_parenthesis_close(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->parenthesis.close++;
	return (COMMAND_VALID);
}
