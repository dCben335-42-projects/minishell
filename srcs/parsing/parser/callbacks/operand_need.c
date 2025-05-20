#include "parsing.h"

t_parse_status	need_right_operand(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->right_operand = REQUIRED;
	return (COMMAND_VALID);
}

t_parse_status	need_no_right_operand(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->right_operand = DISALLOWED;
	return (COMMAND_VALID);
}

t_parse_status	need_right_operand_no_parenthesis(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->right_operand = REQUIRED_WITHOUT_PAREN;
	return (COMMAND_VALID);
}