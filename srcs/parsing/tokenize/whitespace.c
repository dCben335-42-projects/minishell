/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:34:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:37:14 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * 
 * @brief Tokenizes whitespace characters in the input.
 *
 * This function skips over any whitespace characters in the input string
 * and returns a token of type M_SPACE.
 *
 * @param args The lexer arguments containing the input string.
 * @return A pointer to the tokenized whitespace.
 * 
 */
t_ptr	tokenize_whitespace(t_lexer_args *args)
{
	while (ft_isspace(*args->input))
		args->input++;
	return (init_pointer(init_token(M_SPACE, 0, 0), TRUE));
}
