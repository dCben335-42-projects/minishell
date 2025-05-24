#include "messages.h"
#include "minishell.h"
#include "cmd.h"

static const t_token_map_rules	*get_token_map_rules(void)
{
	const int	c_op_rules = ERR_LEFT_OPERAND | EXPECT_CONT | ERR_RIGHT_OPERAND;
	const int	r_rules = ERR_RIGHT_OPERAND_NP;

	static const t_token_map_rules	map[] = {
	{M_EOF, ERR_NO_CLOSE_PAREN, C_METACHAR},
	{M_SPACE, 0, C_METACHAR},

	{TEXT, 0, C_TEXT},
	{QUOTED_TEXT, 0, C_TEXT},
	{EXPAND, 0, C_TEXT},
	{QUOTED_EXPAND, 0, C_TEXT}, 
	{WILDCARD, 0, C_TEXT},

	{OP_OR, c_op_rules, C_OPERATOR},
	{OP_PIPE, c_op_rules, C_OPERATOR},
	{OP_AND, c_op_rules, C_OPERATOR},

	{OP_SEMICOL, ERR_EMPTY_SEMI, C_OPERATOR},
	{OP_PARENTHESIS_OPEN, INC_PAREN_OPEN | EXPECT_CONT | ERR_NO_LEFT_OPERAND, C_PAREN},
	{OP_PARENTHESIS_CLOSE, ERR_NO_OPEN_PAREN | INC_PAREN_CLOSE | ERR_EMPTY_PAREN | ERR_NO_RIGHT_OPERAND, C_PAREN}, 

	{R_IN, r_rules, C_REDIR},
	{R_OUT,	r_rules, C_REDIR},
	{R_APPEND, r_rules, C_REDIR},
	{R_HEREDOC, r_rules, C_REDIR},
	{R_HEREDOC_TRIM, r_rules, C_REDIR},
	{0, 0, 0}
	};

	return (map);
}

static void	calculate_masks(t_masks *masks)
{
	const t_token_map_rules	*map = get_token_map_rules();

	while (map->type)
	{
		if (map->category == C_METACHAR)
			masks->metachar |= map->type;
		else if (map->category == C_TEXT)
			masks->text |= map->type;
		else if (map->category == C_OPERATOR)
			masks->control |= map->type;
		else if (map->category == C_REDIR)
			masks->redir |= map->type;
		else if (map->category == C_PAREN)
			masks->paren |= map->type;
		map++;
	}
	masks->control_extended = masks->control | masks->paren;
}

/**
 * @brief Returns the rules for a given token type.
 *
 * @param token_type The token type to get the rules for.
 * 
 * @return The rules for the token type.
 */
t_uint	get_token_rules(t_token_type token_type)
{
	const t_token_map_rules	*map = get_token_map_rules();

	while (map->type)
	{
		if (map->type == token_type)
			return (map->rules);
		map++;
	}
	return (0);
}

/**
 * @brief Returns the masks for the token types.
 * 
 * @note The masks are calculated only once and stored in a static variable.
 *
 * @return The calculated masks.
 */
t_masks	*get_masks(void)
{
	static t_masks		masks = {0, 0, 0, 0, 0, 0};

	if (!masks.metachar && !masks.text && !masks.control && !masks.redir
		&& !masks.paren && !masks.control_extended)
	{
		calculate_masks(&masks);
	}
	return (&masks);
}


