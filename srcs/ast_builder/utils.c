#include "ast.h"

int	add_previous_cmd(t_ast_node *cmd_master, t_ast_node **cmd_prev, int *i, t_ast_node *cmd, t_get_cmd_master args)
{
	if (cmd)
	{
		(*i)--;
		free(cmd);
	}
	return (add_child_secure(cmd_master, cmd_prev, args));
}

int	add_child_secure(t_ast_node *cmd_master, t_ast_node **cmd_child, t_get_cmd_master args)
{
	if (*cmd_child)
	{
		if (!add_child(cmd_master, *cmd_child))
		{
			printf("add_child_secure\n");
			*(args.has_malloc_error) = TRUE;
			return (0);
		}
		*cmd_child = NULL;
	}
	return (1);
}

t_ast_node	*convert_token_to_cmd_secure(t_token *token, t_get_cmd_master args)
{
	t_ast_node	*cmd;

	cmd = convert_token_to_cmd(token);
	if (!cmd)
	{
		printf("convert_token_to_cmd_secure\n");
		*(args.has_malloc_error) = TRUE;
		return (NULL);
	}
	return (cmd);
}

int add_childs_and_increment(t_ast_node *cmd_master, t_dynamic_array *sub_cmd, int *i, int count)
{
	add_childs(cmd_master, sub_cmd);
	*i += count + 1;
	return (1);
}

void set_dynarray_value_secure(t_dynamic_array *arr, t_uint index, void *value, t_get_cmd_master args)
{
	if (!set_dynarray_value(arr, index, value))
	{
		printf("set_dynarray_value\n");
		*(args.has_malloc_error) = TRUE;
	}
}

void *init_node_secure(t_node_type type, char *value, t_get_cmd_master args)
{
	t_ast_node	*node;

	node = init_node(type, value);
	if (!node)
	{
		printf("init_node_secure\n");
		*(args.has_malloc_error) = TRUE;
		return (NULL);
	}
	return (node);
}

void	simulate_malloc_failure(t_ast_node **cmd)
{
	destroy_dynamic_array((*cmd)->content);
	free(*cmd);
	*cmd = NULL;
}