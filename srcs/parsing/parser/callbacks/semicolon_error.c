#include "parsing.h"

t_parse_status	err_empty_semicol(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!get_prev_token(args, &prev_token) || (is_control_token(*prev_token) && token->type & OP_SEMICOL))
		return (get_error_message(token, "err_empty_semicol"));
	return (COMMAND_VALID);
}