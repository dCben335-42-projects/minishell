#include "parsing.h"
#include "messages.h"

static const t_rules_map	*get_parsing_action_map(void)
{
	static const t_rules_map	parsing_action[] = {
	{INC_PAREN_OPEN,			&increment_parenthesis_open},
	{INC_PAREN_CLOSE,			&increment_parenthesis_close},
	{ERR_NO_OPEN_PAREN,			&err_unopened_parenthesis},
	{ERR_NO_CLOSE_PAREN,		&err_unclosed_parenthesis},
	{ERR_LEFT_OPERAND,			&err_missing_left_operand},
	{ERR_EMPTY_PAREN,			&err_empty_parenthesis},
	{ERR_EMPTY_SEMI,			&err_empty_semicol},
	{ERR_NO_LEFT_OPERAND,		&err_no_left_operand},
	{ERR_RIGHT_OPERAND,			&need_right_operand},
	{ERR_NO_RIGHT_OPERAND,		&need_no_right_operand},
	{ERR_RIGHT_OPERAND_NP,		&need_right_operand_no_parenthesis},
	{0,							NULL}};

	return (parsing_action);
}

static t_parse_status	run_parsing_action(t_lexer_args *args, t_token *token)
{
	const t_rules_map	*map = get_parsing_action_map();
	t_parse_status		status;

	while (map->key)
	{
		if (token->rules & map->key)
		{
			status = map->callback(args, token);
			if (status != COMMAND_VALID)
				return (status);
		}
		map++;
	}
	return (COMMAND_VALID);
}

static t_bool	check_quote(t_lexer_args *args, t_token *token)
{
	if (token->type == M_EOF && args->quote)
	{
		if (args->quote == DELIMITER_EXPANDABLE_TEXT)
			args->not_finished_value = get_readline_arg(READLINE_D_QUOTE_KEY);
		else
			args->not_finished_value = get_readline_arg(READLINE_S_QUOTE_KEY);
		destroy_token(token);
		return (FALSE);
	}
	return (TRUE);
}

t_parse_status	get_error_message(t_token *token, char *msg)
{
	write(2, msg, ft_strlen(msg));
	if (token->value)
	{
		write(2, SYNTAX_ERR_START, ft_strlen(SYNTAX_ERR_START));
		write(2, token->value, ft_strlen(token->value));
		write(2, SYNTAX_ERR_END, ft_strlen(SYNTAX_ERR_END));
	}
	destroy_token(token);
	return (COMMAND_NOT_VALID);
}

t_parse_status	token_parser(t_lexer_args *args, t_token *token)
{
	t_parse_status				status;

	args->rhs = UNDEFINED;
	status = run_parsing_action(args, token);
	if (status == COMMAND_VALID)
		status = check_all_rules(args, token);
	if (status != COMMAND_VALID)
		return (status);
	if (!check_quote(args, token))
		return (COMMAND_NOT_FINISHED);
	if (!push(&args->tokens, token))
	{
		destroy_token(token);
		return (MALLOC_ERROR);
	}
	return (status);
}
