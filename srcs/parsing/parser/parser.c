/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 03:40:01 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 03:42:07 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "config.h"

static const t_rules_map	*get_parsing_action_map(void)
{
	static const t_rules_map	parsing_action[] = {
	{INC_PAREN_OPEN,			&inc_parenthesis_open},
	{INC_PAREN_CLOSE,			&inc_parenthesis_close},
	{ERR_NO_OPEN_PAREN,			&err_unopened_parenthesis},
	{ERR_NO_CLOSE_PAREN,		&err_unclosed_parenthesis},
	{ERR_LEFT_OPERAND,			&err_miss_left_operand},
	{ERR_EMPTY_PAREN,			&err_empty_parenthesis},
	{ERR_EMPTY_SEMI,			&err_empty_semicol},
	{ERR_NO_LEFT_OPERAND,		&err_unexp_left_operand},
	{ERR_RIGHT_OPERAND,			&err_miss_right_operand},
	{ERR_NO_RIGHT_OPERAND,		&err_unexp_right_operand},
	{ERR_RIGHT_OPERAND_NP,		&err_miss_right_operand_np},
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
			status = map->f(args, token);
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
		if (args->quote == SYMBOL_QUOTE_EXPAND)
			args->not_finished_value = get_readline_arg(READLINE_D_QUOTE_KEY);
		else
			args->not_finished_value = get_readline_arg(READLINE_S_QUOTE_KEY);
		destroy_token(token);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Prints an error message for a syntax error.
 *
 * @param token The token that caused the syntax error.
 * @param msg The error message to be printed (not used in this function).
 *
 * @return COMMAND_NOT_VALID indicating that the command is not valid.
 *
 * @note This function prints a syntax error message to stderr
 * and destroys the token before returning.
 */
t_parse_status	print_error_message(t_token *token, char *msg)
{
	(void)msg;
	if (token->value)
	{
		ft_putstr_fd(SYNTAX_ERR_START, 2);
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd(SYNTAX_ERR_END, 2);
	}
	destroy_token(token);
	return (COMMAND_NOT_VALID);
}

/**
 * @brief Parses the tokens and checks for syntax errors.
 *
 * @param args The lexer arguments containing the input string and current state.
 * @param token The token to be parsed.
 * 
 * @note This function runs parsing actions on the provided token and checks
 * if the command is valid. If the command is valid, it checks all rules
 * and pushes the token to the tokens array.
 *
 * @return The status of the parsing:
 * 
 * - `COMMAND_VALID` if the command is valid.
 * 
 * - `COMMAND_NOT_VALID` if there are syntax errors.
 * 
 * - `COMMAND_NOT_FINISHED` if the command is incomplete.
 * 
 * - `MALLOC_ERROR` if memory allocation fails.
 * 
*/
t_parse_status	token_parser(t_lexer_args *args, t_token *token)
{
	t_parse_status	status;

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
