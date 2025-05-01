#include "ast.h"

/**
 * @brief Add a child node to parent node.
 * 
 */
void	add_child_secure(t_ast_node *parent,
	t_ast_node **child, t_get_cmd_master *args)
{
	if (*child)
	{
		if (!add_child(parent, *child))
		{
			args->has_malloc_error = TRUE;
			return ;
		}
		*child = NULL;
	}
}

void	add_childs_and_increment(t_ast_node *cmd_master,
	t_dynarray *sub_cmd, t_uint *i, int count)
{
	add_childs(cmd_master, sub_cmd);
	*i += count + 1;
}

void	set_dynarray_value_secure(t_dynarray *arr,
	t_uint index, void *value, t_get_cmd_master *args)
{
	if (!set_dynarray_value(arr, index, value))
		args->has_malloc_error = TRUE;
}

void	set_cmd_in_cmd_master(t_dynarray *cmd_master,
	t_ast_node **cmd_prev, t_get_cmd_master *args)
{
	if (*cmd_prev)
	{
		set_dynarray_value_secure(cmd_master,
			args->local.pos, *cmd_prev, args);
		*cmd_prev = NULL;
		args->local.pos++;
	}
}
