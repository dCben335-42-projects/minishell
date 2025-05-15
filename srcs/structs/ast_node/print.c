#include "ast_node.h"
#include "ft_printf.h"

t_ast_print_mapping	*get_mappings(void)
{
	static t_ast_print_mapping	mappings[] = {
	{CMD_SEQ,					"CMD_SEQ",				0},
	{CMD_JOIN,					"CMD_BASE",				0},
	{CMD_PARENTHESIS,			"CMD_PARENTHESIS",		0},
	{CMD_WORD,					"CMD_WORD",				0},
	{CMD_SPACE,					"SPACE", 				1},
	{CMD_TAB,					"TAB",					1},
	{CMD_NEWLINE,				"NEWLINE",				1},
	{CMD_TEXT,					"TEXT",					1},
	{CMD_QUOTED_TEXT,			"QUOTED_TEXT",			1},
	{CMD_EXPAND,				"EXPAND",				1},
	{CMD_QUOTED_EXPAND,			"QUOTED_EXPAND",		1},
	{CMD_WILDCARD,				"WILDCARD",				1},
	{CMD_OR,					"CMD_OR",				0},
	{CMD_AMP,					"CMD_AMP",				0},
	{CMD_AND,					"CMD_AND",				0},
	{CMD_SEMICOL,				"CMD_SEMICOL",			0},
	{CMD_DB_SEMICOL,			"CMD_DB_SEMICOL",		0},
	{CMD_SEMICOL_AMP,			"CMD_SEMICOL_AMP",		0},
	{CMD_DB_SEMICOL_AMP,		"CMD_DB_SEMICOL_AMP",	0},
	{CMD_PIPE,					"CMD_PIPE",				0},
	{CMD_PIPE_ERR,				"CMD_PIPE_ERR",			0},
	{CMD_PARENTHESIS_OPEN,		"CMD_PARENTHESIS_OPEN",	0},
	{CMD_PARENTHESIS_CLOSE,		"CMD_PARENTHESIS_CLOSE",0},
	{CMD_REDIR_IN,				"CMD_REDIR_IN",			0},
	{CMD_REDIR_OUT,				"CMD_REDIR_OUT",		0},
	{CMD_APPEND,				"CMD_APPEND",			0},
	{CMD_HEREDOC,				"CMD_HEREDOC",			0},
	{CMD_EOF,					"CMD_EOF",				0},
	};

	return (mappings);
}

void	print_ast_json(t_print_ast_json_args args)
{
	t_uint		i;
	t_uint		j;
	t_ast_node	*node;

	if (!args.cmd)
		return ;
	i = 0;
	while (i < args.cmd->count)
	{
		node = (t_ast_node *)get_dynarray_value(args.cmd, i);
		j = 0;
		while (TRUE)
		{
			//printf("type=[%d]\n ", node->type);
			if ((int)node->type == args.mappings[j].type)
			{
				if (args.mappings[j].use_cmd_join)
					cmd_join(node, i, args.mappings[j].name, args);
				else
					print_ast_node_json(node, i, args.mappings[j].name, args);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	print_ast_json_wrapper(t_dynarray *cmd)
{
	ft_printf("[\n");
	print_ast_json((t_print_ast_json_args){cmd, 2, get_mappings()});
	ft_printf("]\n");
}
