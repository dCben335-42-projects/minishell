/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:20:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 15:53:46 by bcabocel         ###   ########.fr       */
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

typedef enum e_ast_ctx 
{
	CTX_MASTER,
	CTX_PIPE,
	CTX_AND_OR,
	CTX_PARENTHESIS,
}	t_ast_ctx;

//NOTE - cmd is a pointer (t_ast_node **cmd) because we need to
typedef struct s_local_node_info
{
	t_ast_node	*cmd_master;
	int			pos;
	t_ast_node	lcmd;
	t_ast_node	*cmd;
	t_ast_ctx	ctx;
}	t_local_node_info;

typedef struct s_get_cmd_master
{
	t_dynarray			*tokens;
	t_uint				start;
	t_uint				i;
	t_uint				end;
	t_bool				has_malloc_error;
	t_local_node_info	local;
	
}	t_get_cmd_master;

typedef struct s_count_cmd_child
{
	t_uint		count;
	t_bool		space_at_end;
}	t_count_cmd_child;

typedef struct s_get_cmd_primitive
{
	t_count_cmd_child	counter;
	t_ast_node			*cmd_new;
	t_ast_node			*cmd_temp;
	t_bool				*is_empty;
}	t_get_cmd_primitive;

void				get_cmd_master(t_get_cmd_master *args);
void				get_cmd_primitive(t_get_cmd_master *args, t_ast_node **cmd);
int					get_cmd(t_get_cmd_master *args);

void				get_pipe_cmd(
						t_ast_node **cmd_prev,
						t_ast_node *cmd_master,
						t_get_cmd_master *args);

void				get_or_and_cmd_wrapper(
						t_ast_node **cmd_prev,
						t_ast_node *cmd_master,
						t_get_cmd_master *args);

void				get_parenthesis_cmd_master(
						t_ast_node *cmd_master,
						t_get_cmd_master *args);

void				get_parenthesis_cmd(
						t_get_cmd_master *args,
						t_ast_node *cmd_master);

void				add_child(
						t_ast_node *parent,
						t_ast_node **child,
						t_get_cmd_master *args);

t_ast_node			*convert_token_to_cmd_secure(
						t_token *token,
						t_get_cmd_master *args);

t_ast_node			*init_node_secure(
						t_node_type type,
						char *value,
						t_get_cmd_master *args);

t_get_cmd_master	init_t_get_cmd_master(
						t_dynarray *tokens,
						int start,
						int end,
						t_ast_node *cmd_master);

void				get_pipe_cmd_wrapper(
						t_ast_node **cmd_prev,
						t_ast_node *cmd_master,
						t_get_cmd_master *args);

int					is_cmd(t_get_cmd_master *args, size_t mask);

#endif