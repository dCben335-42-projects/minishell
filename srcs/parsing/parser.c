#include "parsing.h"

t_parse_status	get_error_message(t_token *token, char **error)
{
	const size_t	msg_len
		= ft_strlen("erreur de syntaxe près du symbole inattendu « ")
		+ ft_strlen(token->value) + ft_strlen(" »\n") + 1;

	*error = ft_calloc(msg_len, sizeof(char));
	ft_strcat(*error, "erreur de syntaxe près du symbole inattendu «\u00A0");
	ft_strcat(*error, token->value);
	ft_strcat(*error, "\u00A0»\n");
	destroy_token(token);
	return (COMMAND_NOT_VALID);
}

t_parse_status	token_parser(t_lexer_args *args, t_token *token)
{
	int							i;
	t_parse_status				status;
	const t_map_key_callback	parsing_action[] = {
	{INCREMENT_PAREN_OPEN,		&increment_p_open},
	{INCREMENT_PAREN_CLOSE,		&increment_p_close},
	{ERR_UNOPENED_PARENTHESIS,	&err_unopened_parenthesis},
	{ERR_PAREN_NOT_CLOSED,		&err_unclosed_parenthesis},
	{ERR_MISSING_LEFT_OPERAND,	&err_missing_left_operand},
	{ERR_PAREN_EMPTY,			&err_empty_parenthesis},
	{ERR_SEMICOL_EMPTY,			&err_empty_semicol},
	{0,							NULL}
	};

	i = 0;
	status = COMMAND_VALID;
	while (parsing_action[i].key)
	{
		if (token->type & parsing_action[i].key)
			status = parsing_action[i].callback(args, token);
		if (status != COMMAND_VALID)
			return (status);
		i++;
	}
	push(&args->tokens, token);
	return (status);
}
