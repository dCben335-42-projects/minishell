#ifndef AST_H
# define AST_H

# include "node.h"

typedef struct	s_local_node_info
{
	t_dynamic_array	*cmd_master;
	int				pos;
}	t_local_node_info;

typedef struct	s_get_cmd_master
{
    t_dynamic_array		*tokens;
    t_uint				start;
	t_uint				i;
    t_uint				end;
	t_bool				*has_malloc_error;
	t_local_node_info	local_node_info;
}	t_get_cmd_master;


t_dynamic_array	*get_cmd_master(t_get_cmd_master *args);
t_ast_node		*get_cmd(t_get_cmd_master *args, t_bool *is_empty);
void			get_pipe_cmd(t_ast_node *cmd_master, t_get_cmd_master *args, t_ast_node **cmd_prev);
void			get_or_and_cmd(t_ast_node *cmd_master, t_get_cmd_master *args, t_ast_node **cmd_prev);
void			get_or_and_cmd_wrapper(t_ast_node *cmd, t_get_cmd_master *args, t_ast_node **cmd_prev, t_dynamic_array *cmd_master);
void			get_parenthesis_cmd_master(t_get_cmd_master *args, t_dynamic_array *array, int pos);
int				get_parenthesis_cmd(t_get_cmd_master *args, t_ast_node *cmd_master);
int				add_previous_cmd(t_ast_node *cmd_master, t_ast_node **cmd_prev, t_ast_node *cmd, t_get_cmd_master *args);
int				add_childs_and_increment(t_ast_node *cmd_master, t_dynamic_array *sub_cmd, t_uint *i, int count);
int				add_child_secure(t_ast_node *cmd_master, t_ast_node **cmd_child, t_get_cmd_master *args);
void			set_dynarray_value_secure(t_dynamic_array *arr, t_uint index, void *value, t_get_cmd_master *args);
t_ast_node		*convert_token_to_cmd_secure(t_token *token, t_get_cmd_master *args);
void			*init_node_secure(t_node_type type, char *value, t_get_cmd_master *args);
t_get_cmd_master	*init_t_get_cmd_master(t_dynamic_array *tokens, int start, int end, t_bool *has_malloc_error);
void			set_cmd_in_cmd_master(t_dynamic_array *cmd_master, t_ast_node **cmd_prev, t_get_cmd_master *args);
void			get_pipe_cmd_wrapper(t_ast_node *cmd, t_ast_node **cmd_prev, t_get_cmd_master *args, t_dynamic_array *cmd_master);
void			get_parenthesis_cmd_master_wrapper(t_ast_node *cmd, t_dynamic_array *cmd_master, t_ast_node **cmd_prev, t_get_cmd_master *args);
t_bool			is_true_then_false(t_bool *val);
t_dynamic_array	*ast_builder(t_dynamic_array *tokens);

#endif