#include "ast.h"

int	add_child_secure(t_ast_node *cmd_master,
	t_ast_node **cmd_child, t_get_cmd_master *args)
{
	if (*cmd_child)
	{
		if (!add_child(cmd_master, *cmd_child))
		{
			printf("add_child_secure\n");
			*(args->has_malloc_error) = TRUE;
			return (0);
		}
		*cmd_child = NULL;
	}
	return (1);
}

int	add_childs_and_increment(t_ast_node *cmd_master,
	t_dynarray *sub_cmd, t_uint *i, int count)
{
	add_childs(cmd_master, sub_cmd);
	*i += count + 1;
	return (1);
}

int	add_previous_cmd(t_ast_node *cmd_master,
	t_ast_node **cmd_prev, t_ast_node *cmd, t_get_cmd_master *args)
{
	if (cmd)
	{
		args->i--;
		free(cmd);
	}
	return (add_child_secure(cmd_master, cmd_prev, args));
}

void	set_dynarray_value_secure(t_dynarray *arr,
	t_uint index, void *value, t_get_cmd_master *args)
{
	if (!set_dynarray_value(arr, index, value))
	{
		printf("set_dynarray_value\n");
		*(args->has_malloc_error) = TRUE;
	}
}

void	set_cmd_in_cmd_master(t_dynarray *cmd_master,
	t_ast_node **cmd_prev, t_get_cmd_master *args)
{
	if (*cmd_prev)
	{
		set_dynarray_value_secure(cmd_master,
			args->local_node_info.pos, *cmd_prev, args);
		*cmd_prev = NULL;
		args->local_node_info.pos++;
	}
}
