#include "ast_node.h"
#include "ft_printf.h"

static t_ast_print_map	*get_mappings(void)
{
	static t_ast_print_map	map[] = {
	{CMD_SEQ,			"CMD_SEQ",			FALSE},
	{CMD_BASE,			"CMD_BASE",			FALSE},
	{CMD_PARENTHESIS,	"CMD_PARENTHESIS",	FALSE},
	{CMD_WORD,			"CMD_WORD",			FALSE},
	{CMD_TEXT,			"TEXT",				TRUE},
	{CMD_QUOTED_TEXT,	"QUOTED_TEXT",		TRUE},
	{CMD_EXPAND,		"EXPAND",			TRUE},
	{CMD_QUOTED_EXPAND,	"QUOTED_EXPAND",	TRUE},
	{CMD_WILDCARD,		"WILDCARD",			TRUE},
	{CMD_OR,			"CMD_OR",			FALSE},
	{CMD_AND,			"CMD_AND",			FALSE},
	{CMD_PIPE,			"CMD_PIPE",			FALSE},
	{CMD_SEMICOL,		"CMD_SEMICOL",		FALSE},
	{CMD_REDIR_IN,		"CMD_REDIR_IN",		FALSE},
	{CMD_REDIR_OUT,		"CMD_REDIR_OUT",	FALSE},
	{CMD_APPEND,		"CMD_APPEND",		FALSE},
	{CMD_HEREDOC,		"CMD_HEREDOC",		FALSE},
	{CMD_HEREDOC_TRIM,	"CMD_HEREDOC_TRIM",	FALSE},
	{0,					NULL,				FALSE}};

	return (map);
}

static void	print_node(t_ast_node *node, t_uint i, t_print_ast_json_args args)
{
	const t_ast_print_map	*map = get_mappings();

	while (map->type)
	{
		if (node->type == map->type)
		{
			if (map->use_cmd_join)
				cmd_join(node, i, map->name, args);
			else
				print_ast_node_json(node, i, map->name, args);
			return ;
		}
		map++;
	}
}

void	print_ast_json(t_print_ast_json_args args)
{
	t_uint		i;
	t_ast_node	*node;

	if (!args.cmd)
		return ;
	i = 0;
	while (i < args.cmd->count)
	{
		node = (t_ast_node *)get_dynarray_value(args.cmd, i);
		print_node(node, i, args);
		i++;
	}
}

void	print_ast_json_wrapper(t_dynarray *cmd)
{
	printf("[\n");
	print_ast_json((t_print_ast_json_args){cmd, 2});
	printf("]\n");
}
