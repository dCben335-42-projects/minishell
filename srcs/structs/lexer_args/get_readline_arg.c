/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_readline_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:29:41 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/09 23:52:28 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "struct_lexer_args.h"
#include "config.h"

static const t_readline_state	*get_readline_map(void)
{
	static const t_readline_state	map[] = {
	{OP_AND, READLINE_AND_VAL},
	{OP_OR, READLINE_OR_VAL},
	{OP_PIPE, READLINE_PIPE_VAL},
	{R_HEREDOC, READLINE_HEREDOC_VAL},
	{R_HEREDOC_TRIM, READLINE_HEREDOC_TRIM_VAL},
	{READLINE_D_QUOTE_KEY, READLINE_D_QUOTE_VAL},
	{READLINE_S_QUOTE_KEY, READLINE_S_QUOTE_VAL},
	{0, READLINE_PARENTHESIS_VAL}};

	return (map);
}

/**
 * 
 * @brief Gets the readline prefix corresponding to the token type.
 * 
 * @param type The token type for which to get the readline prefix.
 * 
 * @return The corresponding readline prefix as a string.
 * 
*/
const char	*get_readline_arg(t_token_type type)
{
	const t_readline_state	*map = get_readline_map();

	while (map->type)
	{
		if (map->type == type)
			return (map->value);
		map++;
	}
	return (map->value);
}
