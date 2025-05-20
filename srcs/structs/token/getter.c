/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:48 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 16:45:13 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "libft.h"
#include <stdio.h>

static const t_token_map	*get_operator_table(void)
{
	static const t_token_map	op_table[] = {
	{"<<-", R_HEREDOC_TRIM},
	{">>", R_APPEND},
	{"<<", R_HEREDOC},
	{"||", OP_OR},
	{"|&", OP_PIPE_ERR},
	{"&&", OP_AND},
	{"|", OP_PIPE},
	{"&", OP_AMP},
	{">", R_OUT},
	{"<", R_IN},
	{";", OP_SEMICOL},
	{"(", OP_PARENTHESIS_OPEN},
	{")", OP_PARENTHESIS_CLOSE},
	{NULL, M_EOF}};

	return (op_table);
}

/**
 * @brief Function that loop trough the operator table and check if the
 * string starts with an operator and return the token type.
 * 
 * @param str: input string
 * @param offset: offset for the next str after the operator
 * 
 * @note The function will also update the offset if an operator is found
 *  and the offset pointer is not NULL.
 * 
 * @return token type
 */
t_uint	get_token_type(const char *str, int *offset)
{
	const t_token_map	*op_table = get_operator_table();
	size_t				len;

	while (op_table->op)
	{
		len = ft_strlen(op_table->op);
		if (ft_strncmp(str, op_table->op, len) == 0)
		{
			if (offset)
				*offset += len;
			return (op_table->type);
		}
		op_table++;
	}
	return (TEXT);
}

/**
 * @brief Function that return the name of the token type 
 * 	based on the enum (index).
 * 
 * @param type: token type
 * 
 * @return String corresponding to the token type
 */
const char	*get_token_type_name(const t_uint type)
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
