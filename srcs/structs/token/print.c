/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 03:14:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 05:39:52 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "stdio.h"
#include "utils.h"

static const char	*get_token_type_name(const t_uint type)
{
	static const char	*token_name[] = {
		"SPACE",
		"TAB",
		"NEWLINE",
		"EOF",
		"TEXT",
		"QUOTED_TEXT",
		"EXPAND",
		"QUOTED_EXPAND",
		"WILDCARD",
		"OR",
		"PIPE",
		"AND",
		"BACKGROUND",
		"SEMICOL",
		"DB_SEMICOL",
		"SEMICOL_AMP",
		"DB_SEMICOL_AMP",
		"PIPE_ERR",
		"PARENTHESIS_OPEN",
		"PARENTHESIS_CLOSE",
		"R_IN",
		"R_OUT",
		"APPEND",
		"HEREDOC",
		"HEREDOC_TRIM",
	};
	t_uint	i;

	i = 0;
	while ((type & (1 << i)) == 0)
		i++;
	return (token_name[i]);
}

void	print_tokens(t_dynarray *tokens)
{
	t_uint	i;
	t_uint	count;
	t_token	*data;

	i = 0;
	count = tokens->count;
	while (i < count)
	{
		data = (t_token *)get_dynarray_value(tokens, i);
		printf(KEY_COL"%-25s "VALUE_COL"%s\n", get_token_type_name(data->type), data->value);
		i++;
	}
	write(1, RESET_COL, sizeof(RESET_COL));
}