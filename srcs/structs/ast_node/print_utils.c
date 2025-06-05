/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:05:53 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/03 19:10:12 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/**
 * 
 * @brief Prints the AST node in JSON format.
 * 
 * @param node Pointer to the AST node to be printed.
 * @param node_type The stringify type of the AST node.
 * @param args The arguments for printing the AST in JSON format.
 * 
 * @note This function prints the node in a JSON-like format,
 * 
*/
void	print_ast_node_json(
	t_ast_node *node,
	const char *node_type,
	t_ast_printer_ctx args
)
{
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
			print_ast_json(init_printer_ctx(node->content, args.depth + 4));
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
