#include "token.h"
#include "libft.h"
#include <stdio.h>
/**
 * Function to get the operator table
 * @return operator table
 */
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
	{"'", TOKEN_QUOTE},
	{"\"", TOKEN_DQUOTE},
	{"(", TOKEN_OPEN_BRACKET},
	{")", TOKEN_CLOSE_BRACKET},
	{NULL, TOKEN_EOF}};

	return (op_table);
}

/**
 * Function to get the token type
 * @param str: input string
 * @param offset: offset for the next str after the operator
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
 * Function to get the name of the token type
 * @param type: token type
 * @return token name
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
