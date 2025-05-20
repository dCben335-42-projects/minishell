#include "parsing.h"

t_parse_status	err_unopened_parenthesis(t_lexer_args *args, t_token *token)
{
	if (args->parenthesis.close > args->parenthesis.open)
		return (get_error_message(token, "err_unopened_parenthesis"));
	return (COMMAND_VALID);
}

t_parse_status	err_unclosed_parenthesis(t_lexer_args *args, t_token *token)
{
	if (args->parenthesis.open != args->parenthesis.close)
	{
		destroy_token(token);
		token = init_token(M_EOF, NULL, 0);
		return (get_error_message(token, "err_unclosed_parenthesis"));
	}
	return (COMMAND_VALID);
}

t_parse_status	err_empty_parenthesis(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!get_prev_token(args, &prev_token) || (token->type & OP_PARENTHESIS_CLOSE && prev_token->type & OP_PARENTHESIS_OPEN))
		return (get_error_message(token, "err_empty_parenthesis"));
	return (COMMAND_VALID);
}
