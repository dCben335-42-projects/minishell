/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:09:50 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/03 19:10:12 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_node.h"
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

static void	print_node(t_ast_node *node, t_uint i, t_ast_printer_ctx args)
{
	const t_ast_print_map	*map = get_mappings();

	while (map->type)
	{
		if (node->type == map->type)
		{
			if (node->child_count == 1)
			{
				if (i != 0)
					printf(",\n");
				print_ast_node_json(node, map->name, args);
				if (!node->next)
					printf("\n");
			}
			else
				print_ast_node_json(node, map->name, args);
			return ;
		}
		map++;
	}
}

/**
 * 
 * @brief Prints the AST in JSON format.
 * 
 * @param args The arguments containing the command and depth for printing.
 * 
*/
void	print_ast_json(t_ast_printer_ctx args)
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

/**
 * 
 * @brief Initializes the context for printing the AST in JSON format.
 * 
 * @param cmd The dynamic array of command nodes to be printed.
 * 
*/
t_ast_printer_ctx	init_printer_ctx(t_dynarray *cmd)
{
	const t_ast_printer_ctx	args = {
		.cmd = cmd,
		.depth = 2,
		.v_l_brace = BRACE_COL"{\n"RESET_COL,
		.v_r_brace = BRACE_COL"}"RESET_COL,
		.v_l_hook = BRACE_COL"[\n"RESET_COL,
		.v_r_hook = BRACE_COL"]\n"RESET_COL,
		.v_content = FIRST_COL"\"content\": "RESET_COL,
		.f_type = FIRST_COL"\"type\": "SECOND_COL"\"%s\",\n"RESET_COL,
		.f_string = SECOND_COL"\"%s\"\n"RESET_COL
	};

	return (args);
}

/**
 * 
 * @brief Wrapper function to print the AST in JSON format.
 * 
 * @param cmd The dynamic array of command nodes to be printed.
 * 
*/
void	print_ast_json_wrapper(t_dynarray *cmd)
{
	printf("[\n");
	print_ast_json(init_printer_ctx(cmd));
	printf("]\n");
}
