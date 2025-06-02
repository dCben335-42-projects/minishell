/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:20:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/02 20:23:10 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ast_node.h"
# include "struct_dynarray.h"
# include "struct_token.h"
# include "struct_pointer.h"
# include "struct_lexer_args.h"

t_ast_node			*ast_builder(t_dynarray *tokens);

typedef enum e_ast_local_ctx
{
	CTX_MASTER,
	CTX_PIPE,
	CTX_OP,
	CTX_PARENTHESIS,
}	t_ast_local_ctx;

//NOTE - cmd is a pointer (t_ast_node **cmd) because we need to
typedef struct s_local_node_info
{
	t_ast_node	*cmd_master;
	int			pos;
	t_ast_node	lcmd;
	t_ast_node	*cmd;
	t_ast_local_ctx	ctx;
}	t_local_node_info;

/**
 * 
 * @brief Structure to hold the parameters for command parsing.
 * 
 * @param tokens Dynamic array of tokens to be parsed.
 * @param start The starting index of the token array for the current subshell.
 * @param i The current index of the token array for the current subshell.
 * @param end The ending index of the token array for the current subshell.
 * @param has_malloc_error Flag to indicate if a malloc error occurred.
 * 
 * @note start and end are used to define the range of tokens
 * to be treated in the current subshell.
 * 
 * @note a subshell is either a command sequence (CMD_SEQ)
 * or a command parenthesis (CMD_PARENTHESIS).
 * 
*/
typedef struct s_ast_glbctx
{
	t_dynarray			*tokens;
	t_uint				start;
	t_uint				i;
	t_uint				end;
	t_bool				has_malloc_error;
	t_local_node_info	local;
}	t_ast_ctx;

/**
 * 
 * @brief Structure to hold the parameters for command parsing.
 * 
 * @param count Number of command children.
 * @param space_at_end Flag to indicate if there is a space at the end of the command.
*/
typedef struct s_count_cmd_child
{
	t_uint		count;
	t_bool		space_at_end;
}	t_count_cmd_child;

/**
 * 
 * @brief Structure to hold the parameters for command parsing.
 * 
 * @param counter Structure to count command children.
 * @param cmd_new Pointer to the new command node being created.
 * @param cmd_temp Temporary command node.
 * @param is_empty Pointer to a boolean indicating if the command is empty.
 * 
 */
typedef struct s_get_cmd_primitive
{
	t_count_cmd_child	counter;
	t_ast_node			*cmd_new;
	t_ast_node			*cmd_temp;
	t_bool				*is_empty;
}	t_get_cmd_primitive;

void				add_master_cmds(t_ast_ctx *args);
void				get_cmd_primitive(t_ast_ctx *args, t_ast_node **cmd);
t_bool				get_cmd(t_ast_ctx *args);

void				get_pipe_cmd(
						t_ast_node **cmd_prev,
						t_ast_node *cmd_master,
						t_ast_ctx *args);

void				add_op_cmds(
						t_ast_node **cmd_prev,
						t_ast_node *cmd_master,
						t_ast_ctx *args);

void				get_parenthesis_cmd_master(
						t_ast_node *cmd_master,
						t_ast_ctx *args);

void				get_parenthesis_cmd(
						t_ast_ctx *args,
						t_ast_node *cmd_master);

void				add_child(
						t_ast_node *parent,
						t_ast_node **child,
						t_ast_ctx *args);

t_ast_node			*ast_convert_token_to_cmd(
						t_ast_ctx *args,
						t_token *token);

t_ast_node			*ast_init_node(
						t_ast_ctx *args,
						t_node_type type);

t_ast_ctx	init_ast_glbctx(
						t_dynarray *tokens,
						int start,
						int end,
						t_ast_node *cmd_master);

void				get_pipe_cmd_wrapper(
						t_ast_node **cmd_prev,
						t_ast_node *cmd_master,
						t_ast_ctx *args);

int					is_cmd(t_ast_ctx *args, size_t mask);

#endif