#include "parsing.h"

t_parse_status	increment_p_open(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->parenthesis.open++;
	return (COMMAND_VALID);
}

t_parse_status	increment_p_close(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->parenthesis.close++;
	return (COMMAND_VALID);
}

t_parse_status	err_unopened_parenthesis(t_lexer_args *args, t_token *token)
{
	if (args->parenthesis.close > args->parenthesis.open)
		return (get_error_message(token, &args->error, "err_unopened_parenthesis"));
	return (COMMAND_VALID);
}

t_parse_status	err_unclosed_parenthesis(t_lexer_args *args, t_token *token)
{
	if (args->parenthesis.open != args->parenthesis.close)
	{
		destroy_token(token);
		token = init_token(M_EOF, NULL, 0);
		return (get_error_message(token, &args->error, "err_unclosed_parenthesis"));
	}
	return (COMMAND_VALID);
}

t_bool	get_prev_token(t_lexer_args *args, t_token **prev_token)
{
	if (args->tokens.count == 0)
		return (FALSE);
	*prev_token = ((t_token *)get_dynarray_value(&args->tokens, args->tokens.count - 1));
	if ((*prev_token)->type & M_SPACE)
	{
		if (args->tokens.count < 2)
			return (FALSE);
		*prev_token = ((t_token *)get_dynarray_value(&args->tokens, args->tokens.count - 2));
	}
	return (TRUE);
}

t_parse_status	err_missing_left_operand(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!get_prev_token(args, &prev_token) || (!is_text_token(*prev_token) && !(prev_token->type & OP_PARENTHESIS_CLOSE)))
		return (get_error_message(token, &args->error, "err_missing_left_operand"));
	return (COMMAND_VALID);
}

t_parse_status	err_no_left_operand(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!(!get_prev_token(args, &prev_token) || (!is_text_token(*prev_token) && !(prev_token->type & OP_PARENTHESIS_CLOSE))))
		return (get_error_message(token, &args->error, "err_no_left_operand"));
	return (COMMAND_VALID);
}

t_parse_status	err_empty_parenthesis(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!get_prev_token(args, &prev_token) || (token->type & OP_PARENTHESIS_CLOSE && prev_token->type & OP_PARENTHESIS_OPEN))
		return (get_error_message(token, &args->error, "err_empty_parenthesis"));
	return (COMMAND_VALID);
}

t_parse_status	err_empty_semicol(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (!get_prev_token(args, &prev_token) || (is_operator_ext_token(*prev_token) && token->type & OP_SEMICOL))
		return (get_error_message(token, &args->error, "err_empty_semicol"));
	return (COMMAND_VALID);
}

t_parse_status	need_right_operand(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->right_operand = REQUIRED;
	return (COMMAND_VALID);
}

t_parse_status	err_no_right_operand(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->right_operand = DISALLOWED;
	return (COMMAND_VALID);
}

t_parse_status	check_all_rules(t_lexer_args *args, t_token *token)
{
	static t_tribool	must_be_operand = UNDEFINED;
	t_token				*prev_token;

	if (must_be_operand == REQUIRED)
	{
		if (token->type & M_SPACE)
			return (COMMAND_VALID);
		if (is_text_token(*token) || token->type == OP_PARENTHESIS_OPEN)
		{
			must_be_operand = UNDEFINED;
			return (COMMAND_VALID);
		}
		else if (token->type & M_EOF && get_prev_token(args, &prev_token) && prev_token->rules & EXPECT_CONT)
			return (COMMAND_NOT_FINISHED);
		must_be_operand = UNDEFINED;
		return (get_error_message(token, &args->error, "err_missing_right_operand"));
	}
	if (must_be_operand == DISALLOWED)
	{
		if (token->type & M_SPACE)
			return (COMMAND_VALID);
		if (!(is_text_token(*token) || token->type == OP_PARENTHESIS_OPEN))
		{
			must_be_operand = UNDEFINED;
			return (COMMAND_VALID);
		}
		must_be_operand = UNDEFINED;
		return (get_error_message(token, &args->error, "err_no_right_operand"));
	}
	if (args->right_operand == REQUIRED)
	{
		args->right_operand = UNDEFINED;
		must_be_operand = REQUIRED;
	}
	else if (args->right_operand == DISALLOWED)
	{
		args->right_operand = UNDEFINED;
		must_be_operand = DISALLOWED;
	}
	return (COMMAND_VALID);
}
