#include "node.h"
#include "ft_printf.h"

t_ast_print_mapping	*get_mappings(void)
{
	static t_ast_print_mapping	mappings[] = {
	{CMD_PARENTHESIS, "CMD_PARENTHESIS", 0},
	{CMD, "CMD", 0},
	{CMD_AND, "CMD_AND", 0},
	{CMD_OR, "CMD_OR", 0},
	{CMD_PIPE, "CMD_PIPE", 0},
	{CMD_TEXT, "CMD_TEXT", 1},
	{CMD_LITERAL_TEXT, "CMD_LITERAL_TEXT", 1},
	{CMD_VAR_TEXT, "CMD_VAR_TEXT", 1},
	{CMD_REDIR_IN, "CMD_REDIR_IN", 1},
	{CMD_REDIR_OUT, "CMD_REDIR_OUT", 1},
	{CMD_APPEND, "CMD_APPEND", 1},
	{CMD_HEREDOC, "CMD_HEREDOC", 1},
	{CMD_SPACE, "CMD_SPACE", 1},
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
		node = (t_ast_node *)get_value(args.cmd, i);
		j = 0;
		while (TRUE)
		{
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

void	print_ast_json_wrapper(t_dynamic_array *cmd)
{
	ft_printf("[\n");
	print_ast_json((t_print_ast_json_args){cmd, 2, get_mappings()});
	ft_printf("]\n");
}
