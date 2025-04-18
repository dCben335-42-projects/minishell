/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:33:47 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 20:54:23 by bcabocel         ###   ########.fr       */
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
	CMD_SEQ,
	CMD_PARENTHESIS,
	CMD,
	CMD_TEXT,
	CMD_VAR_TEXT,
	CMD_LITERAL_TEXT,
	CMD_AND,
	CMD_OR,
	CMD_PIPE,
	CMD_PARENTHESIS_OPEN,
	CMD_PARENTHESIS_CLOSE,
	CMD_APPEND,
	CMD_REDIR_IN,
	CMD_REDIR_OUT,
	CMD_HEREDOC,
	CMD_SPACE,
	CMD_EOF,
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type	type;
	void		*content;
	int			child_count;
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
	t_token_type	token;
	t_node_type		cmd;
}	t_token_node_map;

t_ast_node	*init_node(t_node_type type, char *value);
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
int			add_childs(t_ast_node *parent, t_dynarray *child);
void		cmd_join(t_ast_node *node, t_uint index,
				const char *name, t_print_ast_json_args args);
void		print_ast_node_json(t_ast_node *node, t_uint i,
				const char *node_type, t_print_ast_json_args args);

#endif