/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_ast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 03:11:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/06 03:15:03 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_AST_H
# define STRUCT_AST_H

# include "struct_dynarray.h"
# include "struct_token.h"
# include "libft.h"
# include <stdio.h>

/**
 * @brief Enumeration representing the different types of nodes in the AST.
*/
typedef enum e_node_type
{
	CMD_SEQ					= 1 << 0,
	CMD_BASE				= 1 << 1,
	CMD_PARENTHESIS			= 1 << 2,
	CMD_TEXT				= 1 << 3,
	CMD_QUOTED_TEXT			= 1 << 4,
	CMD_EXPAND				= 1 << 5,
	CMD_QUOTED_EXPAND		= 1 << 6,
	CMD_WILDCARD			= 1 << 7,
	CMD_OR					= 1 << 8,
	CMD_AND					= 1 << 9,
	CMD_SEMICOL				= 1 << 10,
	CMD_PIPE				= 1 << 11,
	CMD_PARENTHESIS_OPEN	= 1 << 12,
	CMD_PARENTHESIS_CLOSE	= 1 << 13,
	CMD_REDIR_IN			= 1 << 14,
	CMD_REDIR_OUT			= 1 << 15,
	CMD_APPEND				= 1 << 16,
	CMD_HEREDOC				= 1 << 17,
	CMD_HEREDOC_TRIM		= 1 << 18,
	CMD_EOF					= 1 << 19,
	CMD_WORD				= 1 << 20,
}	t_node_type;

/**
 * 
 * @brief Structure representing a node in the Abstract Syntax Tree (AST).
 * 
 * @param type The type of the node, represented by a bitmask.
 * @param content Pointer to the content of the node,
 * which can be a string or a dynamic array.
 * @param child_count The number of children the node has (see note).
 * @param parent Pointer to the parent node in the AST.
 * @param next Pointer to the next sibling node in the AST.
 * 
 * @note child_count = 0 -> content = NULL
 * @note child_count = 1 -> content = char *
 * @note child_count = 2 + n -> content = t_dynarray * with n children
 * 
*/
typedef struct s_ast
{
	t_node_type			type;
	void				*content;
	int					child_count;
	struct s_ast		*parent;
	struct s_ast		*next;
}	t_ast;

t_ast				*init_ast_node(t_node_type type, char *value);
void				reset_ast_node(t_ast *node, t_node_type type);

void				*destroy_ast(t_ast *node);

void				add_ast_childs(t_ast *parent, t_dynarray *childs);
int					add_ast_child_primitive(t_ast *parent, t_ast *child);

int					is_ast_types(t_ast *node, size_t mask);
int					is_ast_wildcard(t_ast *node);

/**
 * @brief Structure to associate token types with AST node types.
 * 
 * @param type The type of the token.
 * @param cmd The corresponding AST node type.
 * 
*/
typedef struct s_convert_map
{
	t_uint			type;
	t_node_type		cmd;
}	t_convert_map;

t_ast				*convert_token_to_ast(t_token *token);

/**
 * 
 * @brief Structure to associate AST node types with
 * their string representations.
 * 
 * @param type The type of the AST node.
 * @param name The string representation of the AST node type.
 * 
 * @note This structure is used for printing the AST in JSON format.
 * 
*/
typedef struct s_ast_print_mapping
{
	t_node_type		type;
	const char		*name;
}	t_ast_print_map;

/**
 * 
 * @brief Structure to hold the arguments for printing the AST in JSON format.
 * 
 * @param cmd Dynamic array of command nodes to be printed.
 * @param depth The current depth in the AST for indentation.
 * @param v_l_brace The string representation of the left brace for JSON.
 * @param v_r_brace The string representation of the right brace for JSON.
 * @param v_l_hook The string representation of the left hook for JSON.
 * @param v_r_hook The string representation of the right hook for JSON.
 * @param v_content The string representation of the content field in JSON.
 * @param f_type The format string for the type field in JSON.
 * @param f_string The format string for string content in JSON.
 * 
*/
typedef struct s_print_ast_json_args
{
	t_dynarray	*cmd;
	t_uint		depth;
	const char	*v_l_brace;
	const char	*v_r_brace;
	const char	*v_l_hook;
	const char	*v_r_hook;
	const char	*v_content;
	const char	*f_type;
	const char	*f_string;
}	t_ast_printer_ctx;

t_ast_printer_ctx	init_ast_printer_ctx(t_dynarray *cmd, t_uint depth);
void				print_ast(t_dynarray *cmd);
void				print_ast_cmd(t_ast_printer_ctx args);
void				print_ast_node(
						t_ast_printer_ctx args,
						t_ast *node,
						t_bool is_first);

#endif