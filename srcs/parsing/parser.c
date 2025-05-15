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
	{INC_PAREN_OPEN,			&increment_p_open},
	{INC_PAREN_CLOSE,			&increment_p_close},
	{ERR_NO_OPEN_PAREN,			&err_unopened_parenthesis},
	{ERR_NO_CLOSE_PAREN,		&err_unclosed_parenthesis},
	{ERR_LEFT_OPERAND,			&err_missing_left_operand},
	{ERR_EMPTY_PAREN,			&err_empty_parenthesis},
	{ERR_EMPTY_SEMI,			&err_empty_semicol},
	{ERR_RIGHT_OPERAND,			&need_right_operand},
	{0,							NULL}
	};

	i = 0;
	status = COMMAND_VALID;
	args->need_right_operand = FALSE;
	while (parsing_action[i].key)
	{
		if (token->rules & parsing_action[i].key)
			status = parsing_action[i].callback(args, token);
		if (status != COMMAND_VALID)
			return (status);
		i++;
	}
	status = check_all_rules(args, token);
	if (status != COMMAND_VALID)
		return (status);
	push(&args->tokens, token);
	return (status);
}
