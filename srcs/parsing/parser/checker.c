#include "parsing.h"

static t_parse_status check_require_without_parenthesis(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (token->type & M_SPACE)
		return (COMMAND_VALID);
	args->expected_rhs = UNDEFINED;
	if (is_text_token(token))
		return (COMMAND_VALID);
	if (token->type & M_EOF && get_prev_token(args, &prev_token) 
		&& prev_token->rules & EXPECT_CONT)
		return (COMMAND_NOT_FINISHED);
	return (print_error_message(token, "err_missing_right_operand_np"));
}

static t_parse_status check_require(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (token->type & M_SPACE)
		return (COMMAND_VALID);
	args->expected_rhs = UNDEFINED;
	if (is_text_token(token) || is_redir_token(token) || token->type == OP_PARENTHESIS_OPEN)
		return (COMMAND_VALID);
	if (token->type & M_EOF && get_prev_token(args, &prev_token) && prev_token->rules & EXPECT_CONT)
		return (COMMAND_NOT_FINISHED);
	return (print_error_message(token, "err_missing_right_operand"));
}

static t_parse_status check_disallowed(t_lexer_args *args, t_token *token)
{
	if (token->type & M_SPACE)
		return (COMMAND_VALID);
	args->expected_rhs = UNDEFINED;
	if (!(is_text_token(token) || token->type == OP_PARENTHESIS_OPEN))
		return (COMMAND_VALID);
	return (print_error_message(token, "err_no_right_operand"));
}

t_parse_status	check_all_rules(t_lexer_args *args, t_token *token)
{
	if (args->expected_rhs == REQUIRED_WITHOUT_PAREN)
		return (check_require_without_parenthesis(args, token));
	if (args->expected_rhs == REQUIRED)
		return (check_require(args, token));
	if (args->expected_rhs == DISALLOWED)
		return (check_disallowed(args, token));
	args->expected_rhs = args->rhs;
	args->rhs = UNDEFINED;
	return (COMMAND_VALID);
}
