/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 03:14:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 06:40:42 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "stdio.h"
#include "utils.h"

typedef struct s_token_print
{
	t_uint		type;
	const char	*name;
}	t_token_print;

static const t_token_print	*get_print_map(void)
{
	static const t_token_print	map[] = {
		{M_SPACE, "SPACE"},
		{M_TAB, "TAB"},
		{M_NEWLINE, "NEWLINE"},
		{M_EOF, "EOF"},
		{TEXT, "TEXT"},
		{QUOTED_TEXT, "QUOTED_TEXT"},
		{EXPAND, "EXPAND"},
		{QUOTED_EXPAND, "QUOTED_EXPAND"},
		{WILDCARD, "WILDCARD"},
		{OP_OR, "OR"},
		{OP_PIPE, "PIPE"},
		{OP_AND, "AND"},
		{OP_SEMICOL, "SEMICOL"},
		{OP_PARENTHESIS_OPEN, "PARENTHESIS_OPEN"},
		{OP_PARENTHESIS_CLOSE, "PARENTHESIS_CLOSE"},
		{R_IN, "R_IN"},
		{R_OUT, "R_OUT"},
		{R_APPEND, "APPEND"},
		{R_HEREDOC, "HEREDOC"},
		{R_HEREDOC_TRIM, "HEREDOC_TRIM"},
		{0, NULL},
	};
	
	return (map);
}

static const char	*get_token_type_name(t_token_type type)
{
	const t_token_print	*map = get_print_map();

	while (map->type)
	{
		if (map->type == type)
			return ((char *)map->name);
		map++;
	}
	return ("UNKNOWN");
}

/**
 * @brief Prints the tokens in the dynamic array.
 *
 * @param tokens The dynamic array of tokens to print.
 */
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