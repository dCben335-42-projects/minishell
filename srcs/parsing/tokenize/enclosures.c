/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enclosures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:21:40 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 22:20:23 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "config.h"

static t_ptr	return_token(
	t_lexer_args *args,
	char **start_i,
	t_token_type *current_type,
	const char quote
)
{
	t_ptr	pointer;
	size_t	len;

	args->input++;
	len = args->input - *start_i - 1;
	pointer = wrap_ptr_token(args, current_type, start_i, len);
	if (args->quote == quote)
		args->quote = 0;
	else
		args->quote = quote;
	return (pointer);
}

static t_ptr	handler_enclosure(
	t_lexer_args *args,
	char **start_i,
	t_token_type *current_type,
	const char quote
)
{
	if (*args->input == quote)
	{
		if (args->quote == 0)
		{
			if (need_tokenize(args, start_i))
				return (return_token(args, start_i, current_type, quote));
			args->quote = quote;
			(*start_i)++;
		}
		else if (args->quote == quote)
		{
			if (need_tokenize(args, start_i))
				return (return_token(args, start_i, current_type, quote));
			args->quote = 0;
		}
	}
	return (init_pointer(NULL, FALSE));
}

static t_bool	is_directly_closed(const char *input, const char quote)
{
	if (!quote && *input == SYMBOL_QUOTE_EXPAND
		&& *(input + 1) == SYMBOL_QUOTE_EXPAND)
		return (TRUE);
	if (!quote && *input == SYMBOL_QUOTE_LITERAL
		&& *(input + 1) == SYMBOL_QUOTE_LITERAL)
		return (TRUE);
	return (FALSE);
}

static t_ptr	handler_enclosures(
	t_lexer_args *args,
	char **start_i,
	t_token_type *current_type
)
{
	t_ptr	pointer;

	if (is_directly_closed(args->input, args->quote))
	{
		if (need_tokenize(args, start_i))
			return (wrap_ptr_token(args, current_type, start_i, 0));
		args->input += 2;
		return (init_pointer(init_token(QUOTED_TEXT, NULL, 0), TRUE));
	}
	pointer = handler_enclosure(args, start_i,
			current_type, SYMBOL_QUOTE_EXPAND);
	if (pointer.is_malloc)
		return (pointer);
	return (handler_enclosure(args, start_i,
			current_type, SYMBOL_QUOTE_LITERAL));
}

/**
 * @brief Tokenizes enclosures in the input string.
 *
 * This function handles several types of enclosures: quotes,
 * environment variables, and wildcards.
 * It first processes any quotes, then env variables, and finally
 * handles wildcards.
 *
 * @param args The lexer arguments containing the current parsing context.
 * @param start_i Pointer to the start index of the current token.
 * @param current_type Pointer to the current token type being processed.
 * 
 * @return A pointer structure containing the result of the tokenization.
 */
t_ptr	tokenize_enclosures(
	t_lexer_args *args,
	char **start_i,
	t_token_type *current_type
)
{
	t_ptr	ptr;

	ptr = handler_enclosures(args, start_i, current_type);
	if (ptr.is_malloc)
		return (ptr);
	ptr = tokenize_expand(args, start_i, current_type);
	if (ptr.is_malloc)
		return (ptr);
	return (tokenize_wildcard(args, current_type));
}
