#include "ast_node.h"
#include "ft_printf.h"

static void	print_indentation(t_uint depth)
{
	while (depth--)
		ft_printf("  ");
}

static void	print_indent_text(t_uint depth, const char *text)
{
	print_indentation(depth);
	ft_printf("%s", text);
}

static void	print_indent_text_format(t_uint depth,
	const char *format, const char *text)
{
	if (format)
	{
		print_indentation(depth);
		ft_printf(format, text);
		return ;
	}
	print_indent_text(depth, text);
}

void	print_ast_node_json(t_ast_node *node,
	t_uint i, const char *node_type, t_print_ast_json_args args)
{
	print_indent_text(args.depth, "{\n");
	print_indent_text_format(args.depth + 2, "type: '%s',\n", node_type);
	if (node->content)
	{
		print_indent_text(args.depth + 2, "content: ");
		if (node->child_count == 1)
		{
			ft_printf("'%s'\n", (char *)node->content);
			print_indent_text(args.depth, "}");
		}
		if (node->child_count > 2)
		{
			ft_printf("[\n");
			print_ast_json((t_print_ast_json_args){
				(t_dynarray *)node->content,
				args.depth + 4, args.mappings});
			print_indent_text(args.depth + 2, "]\n");
			print_indent_text(args.depth, "}");
			if (i < args.cmd->count - 1)
				ft_printf(",");
			ft_printf("\n");
		}
	}
	else
		print_indent_text(args.depth, "}");
}

void	cmd_join(t_ast_node *node,
	t_uint index, const char *name, t_print_ast_json_args args)
{
	if (index != 0)
		ft_printf(",\n");
	print_ast_node_json(node, index, name, args);
	if (index == args.cmd->count - 1)
		ft_printf("\n");
}
