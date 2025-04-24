/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:48 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:48:48 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "libft.h"

static const t_token_map	*get_operator_table(void)
{
	static const t_token_map	op_table[] = {
	{">>", TOKEN_APPEND},
	{"<<", TOKEN_HEREDOC},
	{"||", TOKEN_OR},
	{"|&", TOKEN_PIPE_ERR},
	{"&&", TOKEN_AND},
	{"|", TOKEN_PIPE},
	{"&", TOKEN_AMP},
	{">", TOKEN_REDIR_OUT},
	{"<", TOKEN_REDIR_IN},
	{";", TOKEN_SEMICOL},
	{"'", TOKEN_QUOTE},
	{"\"", TOKEN_DQUOTE},
	{"(", TOKEN_PARENTHESIS_OPEN},
	{")", TOKEN_PARENTHESIS_CLOSE},
	{NULL, TOKEN_EOF}};

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
		if (ft_strncmp(str, op_table->op, len) == 0)
		{
			if (offset)
				*offset += len;
			return (op_table->token);
		}
		op_table++;
	}
	return (TOKEN_TEXT);
}

/**
 * @brief Function that return the name of the token type 
 * 	based on the enum (index).
 * 
 * @param type: token type
 * 
 * @return String corresponding to the token type
 */
const char	*get_token_type_name(const t_token_type type)
{
	static const char	*token_name[] = {
		"TEXT",
		"VAR_TEXT",
		"LITERAL_TEXT",
		"PIPE",
		"AND",
		"OR",
		"SEMICOL",
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"HEREDOC",
		"BACKGROUND",
		"PIPE_ERR",
		"QUOTE",
		"DQUOTE",
		"OPEN_BRACKET",
		"CLOSE_BRACKET",
		"SPACE",
		"UNKNOWN",
		"EOF",
	};

	return (token_name[type]);
}
