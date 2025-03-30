#ifndef AST_H
# define AST_H

# include "node.h"

typedef struct	s_local_node_info
{
	t_dynamic_array	*cmd_master;
	int				*pos;
}	t_local_node_info;

typedef struct	s_get_cmd_master
{
    t_dynamic_array		*tokens;
    int					start;
    int					end;
	t_local_node_info	local_node_info;
}	t_get_cmd_master;


t_dynamic_array	*get_cmd_master(t_get_cmd_master args);
t_ast_node		*get_cmd(t_dynamic_array *tokens, int *i, int end);
int				get_pipe_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev);
int				get_or_and_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev);
void			get_or_and_cmd_wrapper(t_ast_node *cmd, t_get_cmd_master args, int *i, t_ast_node **cmd_prev);
int				get_parenthesis_cmd_master(t_get_cmd_master args, t_dynamic_array *array, int *i, int pos);
int				get_parenthesis_cmd(t_get_cmd_master args, t_ast_node *cmd_master, int *i);
int				add_previous_cmd(t_ast_node *cmd, t_ast_node **cmd_prev, int *i, t_bool decrement);

#endif