/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:20:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/21 20:53:53 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BUILDER_H
# define AST_BUILDER_H

# include "struct_ast.h"
# include "libft_dynarray.h"
# include "struct_token.h"
# include "libft_ptr.h"
# include "struct_lexer_args.h"

t_ast		*ast_builder(t_dynarray *tokens);

/**
 * @brief Enumeration representing the local context of command nodes.
*/
typedef enum e_ast_local_ctx
{
	CTX_MASTER,
	CTX_PIPE,
	CTX_OP,
	CTX_PARENTHESIS,
}	t_ast_local_ctx;

/**
 * @brief Structure to hold local information for command nodes.
 * 
 * @param cmd_master Pointer to the master command node.
 * @param lcmd Local command node used for temporary storage.
 * @param cmd Pointer to the current command node being processed.
 * @param ctx Context of the command node
 * (master, pipe, operator, or parenthesis).
 * 
*/
typedef struct s_local_node_info
{
	t_ast_local_ctx	ctx;
	t_ast			*cmd_master;
	t_ast			lcmd;
	t_ast			*cmd;
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
 * @param local Local information for command nodes.
 * 
 * @note start and end are used to define the range of tokens
 * to be treated in the current subshell.
 * 
 * @note a subshell is either a command sequence (CMD_SEQ)
 * or a command parenthesis (CMD_SUBSHELL).
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
 * @param space_at_end Flag to indicate if there is a space
 * at the end of the command.
 * 
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
	t_ast				*cmd_new;
	t_ast				*cmd_temp;
	t_ast				*cmd_word;
	t_ast				*cmd_redir;
	t_bool				*is_empty;
}	t_get_cmd_primitive;

t_ast_ctx	init_ast_glbctx(
				t_dynarray *tokens,
				t_uint start,
				t_uint end,
				t_ast *cmd_master);

void		add_master_cmds(t_ast_ctx *args);
void		add_cmd_primitive(t_ast_ctx *args, t_ast **cmd);
t_bool		get_cmd(t_ast_ctx *args);

void		add_pipe_cmds(t_ast **cmd_prev, t_ast *cmd_master, t_ast_ctx *args);
void		add_cmd_pipe(t_ast **cmd_prev, t_ast *cmd_master, t_ast_ctx *args);
void		add_op_cmds(t_ast **cmd_prev, t_ast *cmd_master, t_ast_ctx *args);
void		add_parenthesis_cmd_master(t_ast *cmd_master, t_ast_ctx *args);
void		add_parenthesis_cmd(
				t_ast_ctx *args,
				t_ast *cmd_master,
				t_ast **cmd_prev);

void		add_child(t_ast *parent, t_ast **child, t_ast_ctx *args);
t_ast		*ast_convert_token_to_cmd(t_ast_ctx *args, t_token *token);
t_ast		*ast_init_node(t_ast_ctx *args, t_node_type type);

int			is_cmd(t_ast_ctx *args, size_t mask);
t_bool		ast_merr(t_ast *node, t_ast **out);
t_bool		is_empty(t_ast_ctx *args);

void		handle_sub_redir(
				t_ast_ctx *args,
				t_ast *cmd_master,
				t_ast **cmd);

void		handle_sub_redir2(
				t_ast_ctx *args,
				t_ast **cmd_p,
				t_ast **cmd_prev,
				t_ast *cmd_master);

t_ast		*get_adjacent_cmd(t_ast_ctx *args, int count, t_bool is_redir);
#endif