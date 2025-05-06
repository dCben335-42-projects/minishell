#include "ast_node.h"

const t_token_node_map	*get_token_cmd_map(void)
{
	static const t_token_node_map	map[] = {
	{TOKEN_SPACE,					CMD_SPACE},
	{TOKEN_TAB,						CMD_TAB},
	{TOKEN_NEWLINE,					CMD_NEWLINE},
	{TOKEN_TEXT,					CMD_TEXT},
	{TOKEN_EXPAND,					CMD_EXPAND},
	{TOKEN_WILDCARD,				CMD_WILDCARD},
	{TOKEN_OR,						CMD_OR},
	{TOKEN_BACKGROUND,				CMD_AMP},
	{TOKEN_AND,						CMD_AND},
	{TOKEN_SEMICOL,					CMD_SEMICOL},
	{TOKEN_DB_SEMICOL,				CMD_DB_SEMICOL},
	{TOKEN_SEMICOL_AMP,				CMD_SEMICOL_AMP},
	{TOKEN_DB_SEMICOL_AMP,			CMD_DB_SEMICOL_AMP},
	{TOKEN_PIPE,					CMD_PIPE},
	{TOKEN_PIPE_ERR,				CMD_PIPE_ERR},
	{TOKEN_PARENTHESIS_OPEN,		CMD_PARENTHESIS_OPEN},
	{TOKEN_PARENTHESIS_CLOSE,		CMD_PARENTHESIS_CLOSE},
	{TOKEN_REDIR_IN,				CMD_REDIR_IN},
	{TOKEN_REDIR_OUT,				CMD_REDIR_OUT},
	{TOKEN_APPEND,					CMD_APPEND},
	{TOKEN_HEREDOC,					CMD_HEREDOC},
	{TOKEN_EOF,						CMD_EOF}
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
		if (map[i].token == token->type)
		{
			if (is_text_token(*token) || is_redir_token(*token))
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
