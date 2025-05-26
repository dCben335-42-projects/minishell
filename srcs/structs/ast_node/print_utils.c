#include "ast_node.h"
#include "utils.h"

static void	print_text(t_uint depth,
	const char *format, const char *text)
{	
	const char	*base_format = "%s";

	while (depth--)
		printf("  ");
	if (format)
	{
		printf(format, text);
		return ;
	}
	printf(base_format, text);
}


void	print_ast_node_json(t_ast_node *node,
	t_uint i, const char *node_type, t_print_ast_json_args args)
{
	(void)i; // Unused parameter
	print_text(args.depth, NULL, args.v_l_brace);
	print_text(args.depth + 2, args.f_type, node_type);
	if (node->content)
	{
		print_text(args.depth + 2, NULL, args.v_content);
		if (node->child_count == 1)
			print_text(0, args.f_string, node->content);
		if (node->child_count > 2)
		{
			print_text(0, NULL, args.v_l_hook);
			print_ast_json(init_t_print_ast_json_args(node->content, args.depth + 4));
			print_text(args.depth + 2, NULL, args.v_r_hook);
			print_text(args.depth, NULL, args.v_r_brace);	
		}
	}
	if (node->child_count <= 1)
		print_text(args.depth, NULL, args.v_r_brace);
	if (!node->content || (node->child_count > 2 && node->next))
		printf(",");
	if (!node->content || node->child_count > 2)
		printf("\n");
}

void	cmd_join(t_ast_node *node,
	t_uint index, const char *name, t_print_ast_json_args args)
{
	if (index != 0)
		printf(",\n");
	print_ast_node_json(node, index, name, args);
	if (!node->next)
		printf("\n");
}
