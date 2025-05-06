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
		return (get_error_message(token, &args->error));
	return (COMMAND_VALID);
}

t_parse_status	err_unclosed_parenthesis(t_lexer_args *args, t_token *token)
{
	if (args->parenthesis.open != args->parenthesis.close)
	{
		destroy_token(token);
		token = init_token(TOKEN_EOF, NULL, 0);
		return (get_error_message(token, &args->error));
	}
	return (COMMAND_VALID);
}

t_parse_status	err_missing_left_operand(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (args->tokens.count == 0)
		return (get_error_message(token, &args->error));
	prev_token = ((t_token *)get_dynarray_value(&args->tokens,
		args->tokens.count - 1));
	if (prev_token->type & E_CONTROL_OPERATOR_MASK)
		return (get_error_message(token, &args->error));
	return (COMMAND_VALID);
}

t_parse_status	err_empty_parenthesis(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (args->tokens.count == 0)
		return (get_error_message(token, &args->error));
	prev_token = ((t_token *)get_dynarray_value(&args->tokens, args->tokens.count - 1));
	if (token->type & OP_PARENTHESIS_CLOSE && prev_token->type & OP_PARENTHESIS_OPEN)
		return (get_error_message(token, &args->error));
	return (COMMAND_VALID);
}

t_parse_status	err_empty_semicol(t_lexer_args *args, t_token *token)
{
	t_token	*prev_token;

	if (args->tokens.count == 0)
		return (get_error_message(token, &args->error));
	prev_token = ((t_token *)get_dynarray_value(&args->tokens, args->tokens.count - 1));
	if (prev_token->type & SPACE)
	{
		if (args->tokens.count == 2)
			prev_token = ((t_token *)get_dynarray_value(&args->tokens, args->tokens.count - 2));
		else
			return (get_error_message(token, &args->error));
	}
	if (is_operator_ext_token(*prev_token) && token->type & OP_SEMICOL)
		return (get_error_message(token, &args->error));
	return (COMMAND_VALID);
}

t_parse_status	need_right_operand(t_lexer_args *args, t_token *token)
{
	(void)token;
	args->need_right_operand = TRUE;
	return (COMMAND_VALID);
}

t_parse_status	check_all_rules(t_lexer_args *args, t_token *token)
{
	static t_bool must_be_operand = FALSE;

	if (must_be_operand)
	{
		if (token->type & SPACE)
			return (COMMAND_VALID);
		if (is_text_token(*token))
		{
			must_be_operand = FALSE;
			return (COMMAND_VALID);
		}
		must_be_operand = FALSE;
		return (get_error_message(token, &args->error));
	}
	if (args->need_right_operand)
	{
		args->need_right_operand = FALSE;
		must_be_operand = TRUE;
	}
	return (COMMAND_VALID);
}