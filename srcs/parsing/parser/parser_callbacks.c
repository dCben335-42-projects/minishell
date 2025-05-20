#include "parsing.h"

static t_parse_status handle_require_without_parenthesis(t_lexer_args *args, t_token *token, t_right_operand_status *status)
{
	t_token	*prev_token;

	if (token->type & M_SPACE)
		return (COMMAND_VALID);
	*status = UNDEFINED;
	if (is_text_token(*token))
		return (COMMAND_VALID);
	else if (token->type & M_EOF && get_prev_token(args, &prev_token) 
		&& prev_token->rules & EXPECT_CONT)
		return (COMMAND_NOT_FINISHED);
	return (get_error_message(token, "err_missing_right_operand_np"));
}

static t_parse_status handle_require(t_lexer_args *args, t_token *token, t_right_operand_status *status)
{
	t_token	*prev_token;

	if (token->type & M_SPACE)
		return (COMMAND_VALID);
	*status = UNDEFINED;
	if (is_text_token(*token) || token->type == OP_PARENTHESIS_OPEN)
		return (COMMAND_VALID);
	else if (token->type & M_EOF && get_prev_token(args, &prev_token) && prev_token->rules & EXPECT_CONT)
		return (COMMAND_NOT_FINISHED);
	return (get_error_message(token, "err_missing_right_operand"));
}

static t_parse_status handle_disallowed(t_lexer_args *args, t_token *token, t_right_operand_status *status)
{
	(void)args;
	if (token->type & M_SPACE)
		return (COMMAND_VALID);
	*status = UNDEFINED;
	if (!(is_text_token(*token) || token->type == OP_PARENTHESIS_OPEN))
		return (COMMAND_VALID);
	return (get_error_message(token, "err_no_right_operand"));
}

static t_parse_status handle_right_operand(t_lexer_args *args, t_right_operand_status *status)
{
	if (args->right_operand == REQUIRED_WITHOUT_PAREN)
	{
		args->right_operand = UNDEFINED;
		*status = REQUIRED_WITHOUT_PAREN;
	}
	else if (args->right_operand == REQUIRED)
	{
		args->right_operand = UNDEFINED;
		*status = REQUIRED;
	}
	else if (args->right_operand == DISALLOWED)
	{
		args->right_operand = UNDEFINED;
		*status = DISALLOWED;
	}
	return (COMMAND_VALID);
}

t_parse_status	check_all_rules(t_lexer_args *args, t_token *token)
{
	static t_right_operand_status	must_be_operand = UNDEFINED;

	if (must_be_operand == REQUIRED_WITHOUT_PAREN)
		handle_require_without_parenthesis(args, token, &must_be_operand);
	else if (must_be_operand == REQUIRED)
		handle_require(args, token, &must_be_operand);
	else if (must_be_operand == DISALLOWED)
		handle_disallowed(args, token, &must_be_operand);
	return (handle_right_operand(args, &must_be_operand));
}
