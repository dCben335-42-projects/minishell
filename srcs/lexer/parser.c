#include "parser_lexer.h"

static t_parse_status	get_error_message(t_token *token, char **error)
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

static t_parse_status token_parenthesis_parser(t_lexer_args *args, t_token *token)
{
	if (token->type == TOKEN_OPEN_BRACKET)
		args->parenthesis.open++;
	else if (token->type == TOKEN_CLOSE_BRACKET)
		args->parenthesis.close++;
	if (args->parenthesis.close > args->parenthesis.open)
		return (get_error_message(token, &args->error));
	if (token->type == TOKEN_EOF && args->parenthesis.open != args->parenthesis.close)
	{
		destroy_token(token);
		return (get_error_message(init_token(TOKEN_EOF, "(", 0, 1), &args->error));
	}
	return (COMMAND_VALID);
}

t_parse_status	token_parser(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (token_parenthesis_parser(args, token))
		return (COMMAND_NOT_VALID);
	if (args->tokens.count == 0)
	{
		if (is_operator_token(*token))
			return (get_error_message(token, &args->error));
	}
	else
	{
		prev_token = ((t_token *)get_dynarray_value(&args->tokens,
					args->tokens.count - 1));
		if (is_operator_token(*token) && is_operator_token(*prev_token))
			return (get_error_message(token, &args->error));
		if (prev_token->type == TOKEN_OPEN_BRACKET
			&& token->type == TOKEN_CLOSE_BRACKET)
			return (get_error_message(token, &args->error));
	}
	set_dynarray_value(&args->tokens, args->tokens.count, token);
	return (COMMAND_VALID);
}
