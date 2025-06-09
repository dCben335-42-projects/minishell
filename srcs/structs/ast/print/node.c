/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:09:50 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/09 19:07:48 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_ast.h"
#include "utils.h"

static t_ast_print_map	*get_mappings(void)
{
	static t_ast_print_map	map[] = {
	{CMD_SEQ,			"CMD_SEQ",			},
	{CMD_BASE,			"CMD_BASE",			},
	{CMD_PARENTHESIS,	"CMD_PARENTHESIS",	},
	{CMD_WORD,			"CMD_WORD",			},
	{CMD_TEXT,			"TEXT",				},
	{CMD_QUOTED_TEXT,	"QUOTED_TEXT",		},
	{CMD_EXPAND,		"EXPAND",			},
	{CMD_QUOTED_EXPAND,	"QUOTED_EXPAND",	},
	{CMD_WILDCARD,		"WILDCARD",			},
	{CMD_OR,			"CMD_OR",			},
	{CMD_AND,			"CMD_AND",			},
	{CMD_PIPE,			"CMD_PIPE",			},
	{CMD_SEMICOL,		"CMD_SEMICOL",		},
	{CMD_REDIR_IN,		"CMD_REDIR_IN",		},
	{CMD_REDIR_OUT,		"CMD_REDIR_OUT",	},
	{CMD_APPEND,		"CMD_APPEND",		},
	{CMD_HEREDOC,		"CMD_HEREDOC",		},
	{CMD_HEREDOC_TRIM,	"CMD_HEREDOC_TRIM",	},
	{0,					NULL,				}};

	return (map);
}

static void	print_text(t_uint depth,
	const char *format, const char *text)
{
	const char	*base_format = "%s";

	while (depth--)
		ft_putstr_fd("  ", 1);
	if (format)
	{
		printf(format, text);
		return ;
	}
	printf(base_format, text);
}

static void	print_node_json(
	t_ast_printer_ctx ctx,
	t_ast *node,
	const char *type_name
)
{
	print_text(ctx.depth, NULL, ctx.v_l_brace);
	print_text(ctx.depth + 2, ctx.f_type, type_name);
	if (node->content)
	{
		print_text(ctx.depth + 2, NULL, ctx.v_content);
		if (node->child_count == 1)
			print_text(0, ctx.f_string, node->content);
		if (node->child_count > 2)
		{
			print_text(0, NULL, ctx.v_l_hook);
			print_ast_cmd(init_ast_printer_ctx(node->content, ctx.depth + 4));
			print_text(ctx.depth + 2, NULL, ctx.v_r_hook);
			print_text(ctx.depth, NULL, ctx.v_r_brace);
		}
	}
	if (node->child_count <= 1)
		print_text(ctx.depth, NULL, ctx.v_r_brace);
	if (!node->content || (node->child_count > 2 && node->next))
		print_text(0, ",", NULL);
	if (!node->content || node->child_count > 2)
		print_text(0, "\n", NULL);
}

/**
 * 
 * @brief Prints the AST node in JSON format.
 * 
 * 
 * @param ctx The context containing the printing arguments.
 * @param node Pointer to the AST node to be printed.
 * @param is_first Indicates if this is the first node being printed.
 * 
 * @note This function prints the node in a JSON-like format,
 * 
*/
void	print_ast_node(
	t_ast_printer_ctx ctx,
	t_ast *node,
	t_bool is_first
)
{
	const t_ast_print_map	*map = get_mappings();

	while (map->type)
	{
		if (node->type == map->type)
		{
			if (node->child_count == 1)
			{
				if (!is_first)
					print_text(0, ",", NULL);
				print_node_json(ctx, node, map->name);
				if (!node->next)
					print_text(0, "\n", NULL);
			}
			else
				print_node_json(ctx, node, map->name);
			return ;
		}
		map++;
	}
}
