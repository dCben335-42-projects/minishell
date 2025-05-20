#include "ast_node.h"

const t_token_node_map	*get_token_cmd_map(void)
{
	static const t_token_node_map	map[] = {
	{M_SPACE,					CMD_SPACE},
	{M_TAB,						CMD_TAB},
	{M_NEWLINE,					CMD_NEWLINE},
	{TEXT,						CMD_TEXT},
	{QUOTED_TEXT,				CMD_QUOTED_TEXT},
	{EXPAND,					CMD_EXPAND},
	{QUOTED_EXPAND,				CMD_QUOTED_EXPAND},
	{WILDCARD,					CMD_WILDCARD},
	{OP_OR,						CMD_OR},
	{OP_AMP,					CMD_AMP},
	{OP_AND,					CMD_AND},
	{OP_SEMICOL,				CMD_SEMICOL},
	{OP_DB_SEMICOL,				CMD_DB_SEMICOL},
	{OP_SEMICOL_AMP,			CMD_SEMICOL_AMP},
	{OP_DB_SEMICOL_AMP,			CMD_DB_SEMICOL_AMP},
	{OP_PIPE,					CMD_PIPE},
	{OP_PIPE_ERR,				CMD_PIPE_ERR},
	{OP_PARENTHESIS_OPEN,		CMD_PARENTHESIS_OPEN},
	{OP_PARENTHESIS_CLOSE,		CMD_PARENTHESIS_CLOSE},
	{R_IN,						CMD_REDIR_IN},
	{R_OUT,						CMD_REDIR_OUT},
	{R_APPEND,					CMD_APPEND},
	{R_HEREDOC_TRIM,			CMD_HEREDOC_TRIM},
	{R_HEREDOC,					CMD_HEREDOC},
	{M_EOF,						CMD_EOF}
	};

	return (map);
}

t_ast_node	*convert_token_to_cmd(t_token *token)
{
	const t_token_node_map	*map;
	int						i;

	if (!token)
		return (NULL);
	map = get_token_cmd_map();
	i = 0;
	while (TRUE)
	{
		if (map[i].type == token->type)
		{
			if (is_text_token(*token))
				return (init_node(map[i].cmd, token->value));
			return (init_node(map[i].cmd, NULL));
		}
		i++;
	}
}

//t_ast_node	*convert_token_to_cmd(t_token *token)
//{
//	const t_token_node_map	*map;
//	int						i;

//	if (!token)
//		return (NULL);
//	map = get_token_cmd_map();
//	i = 0;
//	while (TRUE)
//	{
//		if (map[i].token == token->type)
//		{
//			return ()
//		}
//		i++;
//	}
//}
