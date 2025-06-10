/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:31:09 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:37:32 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "struct_env.h"
#include "config.h"

static t_bool	is_env(t_lexer_args *args)
{
	const char	cur_char = *args->input;
	const char	next_char = *(args->input + 1);

	if (cur_char == SYMBOL_VAR_EXPAND
		&& (ft_isalpha(next_char) || next_char == '_' || next_char == '?')
		&& (!args->quote || args->quote == SYMBOL_QUOTE_EXPAND))
		return (TRUE);
	if (cur_char == SYMBOL_VAR_EXPAND && !args->quote && (
			next_char == SYMBOL_QUOTE_EXPAND
			|| next_char == SYMBOL_QUOTE_LITERAL
		))
		return (TRUE);
	return (FALSE);
}

/**
 * 
 * @brief Tokenizes an environment variable expansion.
 *
 * This function checks if the current input can be expanded as an environment
 * variable. If it can, it parses the key length and returns a token of type
 * ENV. If not, it returns a TEXT token with the current input.
 *
 * @param args The lexer arguments containing the input string.
 * @param start_i Pointer to the start index in the input string.
 * @param current_type Pointer to the current token type to be modified.
 *
 * @return A pointer to the tokenized expansion or NULL if no expansion is found.
 * 
 */
t_ptr	tokenize_expand(
	t_lexer_args *args,
	char **start_i,
	t_token_type *current_type
)
{
	size_t	key_len;

	if (FLAG_VAR_EXPANSION && is_env(args))
	{
		if (need_tokenize(args, start_i))
			return (wrap_ptr_token(args, current_type, start_i, 0));
		else
		{
			*current_type = ENV;
			key_len = parse_env_key_len(++args->input);
			if (key_len == 0)
				return (init_pointer(init_token(TEXT, *start_i, 0), TRUE));
			args->input += key_len;
			return (wrap_ptr_token(args, current_type, start_i, key_len + 1));
		}
	}
	return (init_pointer(NULL, FALSE));
}
