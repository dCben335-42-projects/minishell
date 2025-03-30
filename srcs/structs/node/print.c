#include "node.h"

void print_indentation(int depth)
{
	int depth_counter;

	depth_counter = 0;
	while (depth_counter < depth)
	{
		printf("  ");
		depth_counter++;
	}
}

void print_ast_node_json(t_ast_node *node, int i, char *node_type, t_print_ast_json_args args)
{
	print_indentation(args.depth);
	printf("{\n");
	print_indentation(args.depth + 2);
	printf("type: '%s',\n", node_type);
	print_indentation(args.depth + 2);
	printf("content: ");


	if (!node->content)
		printf("'null' }\n");
	if (node->child_count == 1)
	{
		printf("'%s'\n", (char *)node->content);
		print_indentation(args.depth);
		printf("}");
	}


	if (node->child_count > 1)
	{
		printf("[\n");
		print_ast_json((t_print_ast_json_args){(t_dynamic_array *)node->content, args.depth + 4});
		print_indentation(args.depth + 2);
		printf("]\n");
		print_indentation(args.depth);
		printf("}");

		if (i < args.cmd->count - 1)
			printf(",");
		printf("\n");
	}
}

void print_ast_json(t_print_ast_json_args args) {
	int i;
	t_ast_node *node;
	t_ast_node *prev_node;

    if (!args.cmd)
		return;
	i = 0;
	while (i < args.cmd->count)
	{
		node = (t_ast_node *)get_value(args.cmd, i);
		
		// duizhjduzhd
		if (node->type == CMD_PARENTHESIS)
		{
			print_ast_node_json(node, i, "CMD_PARENTHESIS", args);
		}
		else if (node->type == CMD)
		{
			print_ast_node_json(node, i, "CMD", args);
		}
		else if (node->type == CMD_AND)
		{
			print_ast_node_json(node, i, "CMD_AND", args);
		}
		else if (node->type == CMD_OR)
		{
			print_ast_node_json(node, i, "CMD_OR", args);
		}
		else if (node->type == CMD_PIPE)
		{
			print_ast_node_json(node, i, "CMD_PIPE", args);
		}
		else if (node->type == CMD_TEXT)
		{
			if (i != 0)
			{
				printf(",");
				printf("\n");
			}
			print_ast_node_json(node, i, "CMD_TEXT", args);
			if (i == args.cmd->count - 1)
				printf("\n");
		}
		else if (node->type == CMD_LITERAL_TEXT)
		{
			if (i != 0)
			{
				printf(",");
				printf("\n");
			}
			print_ast_node_json(node, i, "CMD_LITERAL_TEXT", args);
			if (i == args.cmd->count - 1)
				printf("\n");
		}
		else if (node->type == CMD_VAR_TEXT)
		{
			if (i != 0)
			{
				printf(",");
				printf("\n");
			}
			print_ast_node_json(node, i, "CMD_VAR_TEXT", args);
			if (i == args.cmd->count - 1)
				printf("\n");
		}
		i++;
		prev_node = node;
	}
}

void print_ast_json_wrapper(t_dynamic_array *cmd)
{
	printf("[\n");
	print_ast_json((t_print_ast_json_args){cmd, 2});
	printf("]\n");
}

void print_cmd_type(t_node_type type)
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