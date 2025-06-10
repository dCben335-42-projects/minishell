/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:37:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:38:30 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "config.h"

static t_bool	is_a_wildcard(t_lexer_args *args, t_token_type *current_type)
{
	if (*current_type == TEXT && !args->quote
		&& *args->input == SYMBOL_GLOB_ANY)
		return (TRUE);
	return (FALSE);
}

/**
 * 
 * @brief Tokenizes a wildcard from the input string.
 *
 * This function checks if the current input is a wildcard character
 * and modifies the current token type accordingly.
 *
 * @param args The lexer arguments containing the input string.
 * @param current_type Pointer to the current token type to be modified.
 *
 * @return A pointer to the tokenized wildcard or NULL if no wildcard is found.
 */
t_ptr	tokenize_wildcard(t_lexer_args *args, t_token_type *current_type)
{
	if (FLAG_WILDCARD_EXPANSION && is_a_wildcard(args, current_type))
		*current_type = WILDCARD;
	return (init_pointer(NULL, FALSE));
}
