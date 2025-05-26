/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:48 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 08:00:55 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "libft.h"
#include <stdio.h>

static const t_token_map	*get_operator_table(void)
{
	static const t_token_map	op_table[] = {
	{"<<-", R_HEREDOC_TRIM},
	{"<<", R_HEREDOC},
	{">>", R_APPEND},
	{"||", OP_OR},
	{"&&", OP_AND},
	{"|", OP_PIPE},
	{";", OP_SEMICOL},
	{"(", OP_PARENTHESIS_OPEN},
	{")", OP_PARENTHESIS_CLOSE},
	{">", R_OUT},
	{"<", R_IN},
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
t_token_type	get_token_type(const char *str, int *offset)
{
	const t_token_map	*op_table = get_operator_table();
	size_t				len;

	while (op_table->op)
	{
		len = ft_strlen(op_table->op);
		if (!ft_strncmp(str, op_table->op, len))
		{
			if (offset)
				*offset += len;
			return (op_table->type);
		}
		op_table++;
	}
	return (TEXT);
}
