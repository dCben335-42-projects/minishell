/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:33:47 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/02 17:26:18 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_NODE_H
# define AST_NODE_H

# include "struct_dynarray.h"
# include "struct_token.h"
# include "libft.h"
# include <stdio.h>

typedef enum e_node_type
{
	CMD_SEQ					= 1 << 0,
	CMD_JOIN				= 1 << 1,
	CMD_PARENTHESIS			= 1 << 2,
	CMD_SPACE				= 1 << 3,
	CMD_TAB					= 1 << 4,
	CMD_NEWLINE				= 1 << 5,
	CMD_TEXT				= 1 << 6,
	CMD_EXPAND				= 1 << 7,
	CMD_WILDCARD			= 1 << 8,
	CMD_OR					= 1 << 9,
	CMD_AMP					= 1 << 10,
	CMD_AND					= 1 << 11,
	CMD_SEMICOL				= 1 << 12,
	CMD_DB_SEMICOL			= 1 << 13,
	CMD_SEMICOL_AMP			= 1 << 14,
	CMD_DB_SEMICOL_AMP		= 1 << 15,
	CMD_PIPE				= 1 << 16,
	CMD_PIPE_ERR			= 1 << 17,
	CMD_PARENTHESIS_OPEN	= 1 << 18,
	CMD_PARENTHESIS_CLOSE	= 1 << 19,
	CMD_REDIR_IN			= 1 << 20,
	CMD_REDIR_OUT			= 1 << 21,
	CMD_APPEND				= 1 << 22,
	CMD_HEREDOC				= 1 << 23,
	CMD_EOF					= 1 << 24,
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	void				*content;
	int					child_count;
	struct s_ast_node	*parent;
	struct s_ast_node	*next;
}	t_ast_node;

typedef struct s_ast_print_mapping
{
	int			type;
	const char	*name;
	int			use_cmd_join;
}	t_ast_print_mapping;

typedef struct s_print_ast_json_args
{
	t_dynarray			*cmd;
	t_uint				depth;
	t_ast_print_mapping	*mappings;
}	t_print_ast_json_args;

typedef struct s_token_node_map
{
	t_token_type_flags	token;
	t_node_type			cmd;
}	t_token_node_map;

t_ast_node	*init_node(t_node_type type, char *value);
void		init_node_on_stack(t_ast_node *node, t_node_type type);
t_ast_node	*convert_token_to_cmd(t_token *token);

/**
 * @brief Add a child node to the parent node.
 * if child_count == 1, it means that the parent node has string as content.
 * if child_count == 2, it means that the parent 
 * node has dynamic array empty as content. (malloc error)
 * if child_count == n, it means that the parent 
 * node has dynamic array with n - 2 child as content.
 */
int			add_child(t_ast_node *parent, t_ast_node *child);
void		print_ast_json_wrapper(t_dynarray *cmd);
void		print_ast_json(t_print_ast_json_args args);
void		*destroy_node(t_ast_node *node);
void		*recursive_destroy_node(t_ast_node *node);
void		add_childs(t_ast_node *parent, t_dynarray *childs);
void		cmd_join(t_ast_node *node, t_uint index,
				const char *name, t_print_ast_json_args args);
void		print_ast_node_json(t_ast_node *node, t_uint i,
				const char *node_type, t_print_ast_json_args args);
int			is_node(t_ast_node *node, size_t mask);

#endif