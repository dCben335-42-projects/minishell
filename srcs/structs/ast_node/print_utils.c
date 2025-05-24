#include "ast_node.h"
#include "utils.h"

static void	print_indentation(t_uint depth)
{
	while (depth--)
		printf("  ");
}

static void	print_indent_text(t_uint depth, const char *text)
{
	print_indentation(depth);
	printf("%s", text);
}

static void	print_indent_text_format(t_uint depth,
	const char *format, const char *text)
{
	if (format)
	{
		print_indentation(depth);
		printf(format, text);
		return ;
	}
	print_indent_text(depth, text);
}

void	print_ast_node_json(t_ast_node *node,
	t_uint i, const char *node_type, t_print_ast_json_args args)
{
	print_indent_text(args.depth, BRACE_COL"{\n"RESET_COL);
	print_indent_text_format(args.depth + 2, FIRST_COL"\"type\": "SECOND_COL"\"%s\",\n"RESET_COL, node_type);
	if (node->content)
	{
		print_indent_text(args.depth + 2, FIRST_COL"\"content\": "RESET_COL);;
		if (node->child_count == 1)
		{
			printf(SECOND_COL"\"%s\"\n"RESET_COL, (char *)node->content);
			print_indent_text(args.depth, BRACE_COL"}"RESET_COL);
		}
		if (node->child_count > 2)
		{
			printf(BRACE_COL"[\n"RESET_COL);
			print_ast_json((t_print_ast_json_args){(t_dynarray *)node->content, args.depth + 4});
			print_indent_text(args.depth + 2, BRACE_COL"]\n"RESET_COL);
			print_indent_text(args.depth, BRACE_COL"}"RESET_COL);
			if (i < args.cmd->count - 1)
				printf(",");
			printf("\n");
		}
	}
	else
		print_indent_text(args.depth, "}");
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
