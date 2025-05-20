#include "parsing.h"
#include "messages.h"


static const t_rules_map	*get_parsing_action(void)
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

/**
 * @brief Function to check whether the command is still in a valid
 * format after the new token has been added.
 * 
 * @param input: input string
 * @param offset: offset of the token
 * 
 * @return the type of the token
 */
t_parse_status	token_parser(t_lexer_args *args, t_token *token)
{
	const t_rules_map	*parsing_action = get_parsing_action();
	t_parse_status				status;

	status = COMMAND_VALID;
	args->right_operand = UNDEFINED;
	while (parsing_action->key)
	{
		if (token->rules & parsing_action->key)
			status = parsing_action->callback(args, token);
		if (status != COMMAND_VALID)
			return (status);
		parsing_action++;
	}
	status = check_all_rules(args, token);
	if (status != COMMAND_VALID)
		return (status);
	if (token->type == M_EOF)
		if (args->quote != 0)
			return (COMMAND_NOT_FINISHED);
	if (!push(&args->tokens, token))
	{
		destroy_token(token);
		return (MALLOC_ERROR);
	}
	return (status);
}
