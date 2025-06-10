/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 00:53:41 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:33:42 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * 
 * @brief Wraps the current token type based on whether it is quoted or not.
 *
 * @param args The lexer arguments containing the quote state.
 * @param current_type Pointer to the current token type to be modified.
 *
 * @return The modified token type.
 * 
 */
t_token_type	quoted_wrapper(t_lexer_args *args, t_token_type *current_type)
{
	if (args->quote)
	{
		if (*current_type == TEXT)
			*current_type = QUOTED_TEXT;
		else if (*current_type == ENV)
			*current_type = QUOTED_EXPAND;
	}
	return (*current_type);
}

/**
 * 
 * @brief Checks if the input string has content to tokenize.
 *
 * @param args The lexer arguments containing the input string.
 * @param start_i Pointer to the start index in the input string.
 *
 * @return A boolean indicating whether there is content to tokenize.
 * 
 */
t_bool	need_tokenize(t_lexer_args *args, char **start_i)
{
	return (args->input - *start_i > 0);
}

/**
 * 
 * @brief Wraps a token pointer with the appropriate type
 * based on the current lexer arguments and the start index.
 *
 * @param args The lexer arguments containing the input and current state.
 * @param current_type The current token type to be wrapped.
 * @param start_i Pointer to the start index in the input string.
 * @param optional_len Optional length of the token, defaults to the length
 * from start_i to args->input if not provided.
 *
 * @return A ptr to the wrapped token pointer.
 * 
 */
t_ptr	wrap_ptr_token(
	t_lexer_args *args,
	t_token_type *current_type,
	char **start_i,
	size_t optional_len
)
{
	t_token			*token;
	t_token_type	type;

	type = quoted_wrapper(args, current_type);
	if (!optional_len)
		optional_len = args->input - *start_i;
	token = init_token(type, *start_i, optional_len);
	return (init_pointer(token, TRUE));
}
