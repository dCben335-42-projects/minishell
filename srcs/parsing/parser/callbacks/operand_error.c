#include "parsing.h"

t_parse_status	err_missing_left_operand(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!get_prev_token(args, &prev_token) 
		|| (!is_text_token(prev_token) && !(prev_token->type & OP_PARENTHESIS_CLOSE)))
		return (get_error_message(token, "err_missing_left_operand"));
	return (COMMAND_VALID);
}

t_parse_status	err_no_left_operand(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!(!get_prev_token(args, &prev_token) 
		|| (!is_text_token(prev_token) && !(prev_token->type & OP_PARENTHESIS_CLOSE))))
		return (get_error_message(token, "err_no_left_operand"));
	return (COMMAND_VALID);
}