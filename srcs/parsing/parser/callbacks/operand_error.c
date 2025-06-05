#include "parsing.h"

/**
 * @brief Handles the case where a left operand is missing.
*/
t_parse_status	err_miss_left_operand(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!get_prev_token(args, &prev_token) 
		|| (!is_text_token(prev_token) && !(prev_token->type & OP_PARENTHESIS_CLOSE)))
		return (get_error_message(token, "err_missing_left_operand"));
	return (COMMAND_VALID);
}

/**
 * @brief Handles the case where a left operand is unexpected.
*/
t_parse_status	err_unexp_left_operand(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!(!get_prev_token(args, &prev_token) 
		|| (!is_text_token(prev_token) && !(prev_token->type & OP_PARENTHESIS_CLOSE))))
		return (get_error_message(token, "err_no_left_operand"));
	return (COMMAND_VALID);
}