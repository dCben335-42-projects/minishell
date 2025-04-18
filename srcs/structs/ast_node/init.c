#include "node.h"

t_ast_node	*init_node(t_node_type type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	if (value)
	{
		node->content = ft_strdup(value);
		node->child_count = 1;
		return (node);
	}
	node->content = NULL;
	node->child_count = 0;
	return (node);
}

int	add_child(t_ast_node *parent, t_ast_node *child)
{
	t_dynamic_array	*sub_cmd;

	if (parent->child_count == 0)
	{
		sub_cmd = init_dynamic_array_malloc(80,
				(void *(*)(void *))recursive_destroy_node);
		if (!sub_cmd)
			return (0);
		if (!set_dynarray_value(sub_cmd, 0, child))
			return (0);
		parent->content = sub_cmd;
		parent->child_count = 3;
		return (1);
	}
	if (!set_dynarray_value(parent->content, parent->child_count - 2, child))
		return (0);
	parent->child_count++;
	return (1);
}

int	add_childs(t_ast_node *parent, t_dynamic_array *child)
{
	parent->content = child;
	parent->child_count = child->count + 2;
	return (1);
}
