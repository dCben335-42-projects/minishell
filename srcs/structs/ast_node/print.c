#include "node.h"

void	print_indentation(int depth)
{
	while (depth--)
		printf("  ");
}

void	print_ast_node_json(t_ast_node *node,
	t_uint i, const char *node_type, t_print_ast_json_args args)
{
	print_indentation(args.depth);
	printf("{\n");
	print_indentation(args.depth + 2);
	printf("type: '%s',\n", node_type);
	if (node->content)
	{
		print_indentation(args.depth + 2);
		printf("content: ");
		if (node->child_count == 1)
		{
			printf("'%s'\n", (char *)node->content);
			print_indentation(args.depth);
			printf("}");
		}
		if (node->child_count > 2)
		{
			printf("[\n");
			print_ast_json((t_print_ast_json_args){
				(t_dynamic_array *)node->content,
				args.depth + 4, args.mappings});
			print_indentation(args.depth + 2);
			printf("]\n");
			print_indentation(args.depth);
			printf("}");
			if (i < args.cmd->count - 1)
				printf(",");
			printf("\n");
		}
	}
	else
	{
		print_indentation(args.depth);
		printf("}");
	}
}

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

void	cmd_join(t_ast_node *node,
	t_uint index, const char *name, t_print_ast_json_args args)
{
	if (index != 0)
		printf(",\n");
	print_ast_node_json(node, index, name, args);
	if (index == args.cmd->count - 1)
		printf("\n");
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
	printf("[\n");
	print_ast_json((t_print_ast_json_args){cmd, 2, get_mappings()});
	printf("]\n");
}

void	print_cmd_type(t_node_type type)
{
	if (type == CMD_SEQ)
		printf("CMD_SEQ\n");
	else if (type == CMD)
		printf("CMD\n");
	else if (type == CMD_PARENTHESIS)
		printf("CMD_PARENTHESIS\n");
	else if (type == CMD_TEXT)
		printf("CMD_TEXT\n");
	else if (type == CMD_VAR_TEXT)
		printf("CMD_VAR_TEXT\n");
	else if (type == CMD_LITERAL_TEXT)
		printf("CMD_LITERAL_TEXT\n");
	else if (type == CMD_AND)
		printf("CMD_AND\n");
	else if (type == CMD_OR)
		printf("CMD_OR\n");
	else if (type == CMD_PIPE)
		printf("CMD_PIPE\n");
	else if (type == CMD_PARENTHESIS_OPEN)
		printf("CMD_PARENTHESIS_OPEN\n");
	else if (type == CMD_PARENTHESIS_CLOSE)
		printf("CMD_PARENTHESIS_CLOSE\n");
	else if (type == CMD_EOF)
		printf("CMD_EOF\n");
}
