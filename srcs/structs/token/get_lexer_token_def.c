#include "messages.h"
#include "minishell.h"
#include "cmd.h"

static const t_token_map_rules	*get_token_map_rules(void)
{
	static const t_token_map_rules	map[] = {
	{M_SPACE, 0, C_METACHAR},
	{M_TAB, 0, C_METACHAR},
	{TEXT, 0, C_TEXT},
	{M_NEWLINE, 0, C_METACHAR},
	{M_NEWLINE, 0, C_METACHAR},
	{QUOTED_TEXT, 0, C_TEXT},
	{EXPAND, 0, C_TEXT},
	{QUOTED_EXPAND, 0, C_TEXT}, 
	{WILDCARD, 0, C_TEXT},
	{OP_OR, ERR_LEFT_OPERAND | EXPECT_CONT | ERR_RIGHT_OPERAND, C_OPERATOR},
	{OP_PIPE, ERR_LEFT_OPERAND | EXPECT_CONT | ERR_RIGHT_OPERAND, C_OPERATOR},
	{OP_AND, ERR_LEFT_OPERAND | EXPECT_CONT | ERR_RIGHT_OPERAND, C_OPERATOR},
	{OP_AMP, ERR_LEFT_OPERAND | EXPECT_CONT, C_OPERATOR},
	{OP_SEMICOL, ERR_EMPTY_SEMI, C_OPERATOR},
	{OP_DB_SEMICOL, ERR_EMPTY_SEMI, C_OPERATOR},
	{OP_SEMICOL_AMP, ERR_EMPTY_SEMI, C_OPERATOR},
	{OP_DB_SEMICOL_AMP, ERR_EMPTY_SEMI, C_OPERATOR},
	{OP_PIPE_ERR, ERR_LEFT_OPERAND | EXPECT_CONT, C_OPERATOR},
	{OP_PARENTHESIS_OPEN, INC_PAREN_OPEN | EXPECT_CONT | ERR_NO_LEFT_OPERAND, C_PAREN},
	{OP_PARENTHESIS_CLOSE, ERR_NO_OPEN_PAREN | INC_PAREN_CLOSE | ERR_EMPTY_PAREN | ERR_NO_RIGHT_OPERAND, C_PAREN}, 
	{R_IN, ERR_RIGHT_OPERAND, C_REDIR}, {R_OUT,	ERR_RIGHT_OPERAND, C_REDIR},
	{R_APPEND, ERR_RIGHT_OPERAND, C_REDIR},
	{R_HEREDOC, ERR_RIGHT_OPERAND, C_REDIR},
	{M_EOF, ERR_NO_CLOSE_PAREN, C_METACHAR},
	{R_HEREDOC_TRIM, ERR_RIGHT_OPERAND, C_REDIR},
	{0, 0, 0}
	};

	return (map);
}

static void	get_masks(t_lexer_token_def *def)
{
	const t_token_map_rules	*map = get_token_map_rules();

	while (map->type)
	{
		if (map->category == C_METACHAR)
			def->masks.metachar |= map->type;
		else if (map->category == C_TEXT)
			def->masks.name |= map->type;
		else if (map->category == C_OPERATOR)
			def->masks.control |= map->type;
		else if (map->category == C_REDIR)
			def->masks.redir |= map->type;
		else if (map->category == C_PAREN)
			def->masks.paren |= map->type;
		map++;
	}
	def->masks.extended = def->masks.control | def->masks.paren;
}

t_lexer_token_def	*get_lexer_token_def(void)
{
	static t_lexer_token_def	lexer_token_def = {
		.masks = {0, 0, 0, 0, 0},
		.map = NULL,
	};

	if (!lexer_token_def.map)
	{
		printf("init lexer_token_def\n");
		lexer_token_def.map = get_token_map_rules();
		get_masks(&lexer_token_def);
	}
	return (&lexer_token_def);
}

t_uint	get_rules(t_uint token_type)
{
	const t_token_map_rules	*map = get_token_map_rules();
	t_uint					i;

	i = 0;
	while (map[i].type)
	{
		if (map[i].type == token_type)
			return (map[i].rules);
		i++;
	}
	return (0);
}