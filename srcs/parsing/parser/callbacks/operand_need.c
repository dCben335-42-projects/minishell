#include "parsing.h"

t_parse_status	err_miss_right_operand(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->rhs = REQUIRED;
	return (COMMAND_VALID);
}

t_parse_status	err_unexp_right_operand(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->rhs = DISALLOWED;
	return (COMMAND_VALID);
}

t_parse_status	err_miss_right_operand_np(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->rhs = REQUIRED_WITHOUT_PAREN;
	return (COMMAND_VALID);
}