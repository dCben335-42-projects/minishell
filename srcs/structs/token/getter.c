/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:15:48 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/05 15:58:52 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_token.h"
#include "libft.h"
#include <stdio.h>

static const t_token_map	*get_operator_table(void)
{
	static const t_token_map	op_table[] = {
	{">>", TOKEN_APPEND},
	{"<<", TOKEN_HEREDOC},
	{"||", TOKEN_OR},
	{"|&", TOKEN_PIPE_ERR},
	{"&&", TOKEN_AND},
	{"|", TOKEN_PIPE},
	{"&", TOKEN_BACKGROUND},
	{">", TOKEN_REDIR_OUT},
	{"<", TOKEN_REDIR_IN},
	{";", TOKEN_SEMICOL},
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
t_token_type_flags	get_token_type(const char *str, int *offset)
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
const char	*get_token_type_name(const t_token_type_flags type)
{
	static const char	*token_name[] = {
		"SPACE",
		"TAB",
		"NEWLINE",
		"TEXT",
		"EXPAND",
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
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"HEREDOC",
		"EOF",
	};
	t_uint	i;

	i = 0;
	while ((type & (1 << i)) == 0)
		i++;
	printf("vad=%s\n", token_name[i]);
	return (token_name[i]);
}


	//TOKEN_SPACE					= SPACE,
	//TOKEN_TAB					= TAB,
	//TOKEN_NEWLINE				= NEWLINE,
	//TOKEN_TEXT					= TEXT,
	//TOKEN_EXPAND				= EXPAND,
	//TOKEN_WILDCARD				= WILDCARD,
	//TOKEN_OR					= OP_OR | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	//TOKEN_PIPE					= OP_PIPE | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	//TOKEN_AND					= OP_AND | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	//TOKEN_BACKGROUND			= OP_AMP | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	//TOKEN_SEMICOL				= OP_SEMICOL | ERR_MISSING_LEFT_OPERAND,
	//TOKEN_DB_SEMICOL			= OP_DB_SEMICOL | ERR_MISSING_LEFT_OPERAND,
	//TOKEN_SEMICOL_AMP			= OP_SEMICOL_AMP | ERR_MISSING_LEFT_OPERAND,
	//TOKEN_DB_SEMICOL_AMP		= OP_DB_SEMICOL_AMP | ERR_MISSING_LEFT_OPERAND,
	//TOKEN_PIPE_ERR				= OP_PIPE_ERR | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	//TOKEN_PARENTHESIS_OPEN		= OP_PARENTHESIS_OPEN | EXPECT_CONTINUATION | INCREMENT_PAREN_OPEN,
	//TOKEN_PARENTHESIS_CLOSE		= OP_PARENTHESIS_CLOSE | ERR_UNOPENED_PARENTHESIS | INCREMENT_PAREN_CLOSE | ERR_PAREN_EMPTY,
	//TOKEN_REDIR_IN				= REDIR_IN | ERR_MISSING_LEFT_OPERAND,
	//TOKEN_REDIR_OUT				= REDIR_OUT | ERR_MISSING_LEFT_OPERAND,
	//TOKEN_APPEND				= REDIR_APPEND | ERR_MISSING_LEFT_OPERAND,
	//TOKEN_HEREDOC				= REDIR_HEREDOC | ERR_MISSING_LEFT_OPERAND,
	//TOKEN_EOF					= 1 << 21 | ERR_PAREN_NOT_CLOSED,	// EOF