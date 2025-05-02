#include "ast_node.h"

t_ast_node	*init_node(t_node_type type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->parent = NULL;
	node->next = NULL;
	if (value)
	{
		node->content = ft_strdup(value);
		if (!node->content)
		{
			free(node);
			return (NULL);
		}
		node->child_count = 1;
		return (node);
	}
	node->content = NULL;
	node->child_count = 0;
	return (node);
}

void	init_node_on_stack(t_ast_node *node, t_node_type type)
{
	node->type = type;
	node->parent = NULL;
	node->next = NULL;
	node->content = NULL;
	node->child_count = 0;
}

int	add_child(t_ast_node *parent, t_ast_node *child)
{
	t_dynarray	*sub_cmd;

	child->parent = parent;
	if (parent->child_count == 0)
	{
		sub_cmd = init_dynarray_malloc(80,
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
	((t_ast_node *)get_dynarray_value(parent->content, parent->child_count - 3))->next = child;
	parent->child_count++;
	return (1);
}

void	add_childs(t_ast_node *parent, t_dynarray *childs)
{
	t_uint	i;

	i = 0;
	while (i < childs->count)
	{
		if (i > 0)
			((t_ast_node *)get_dynarray_value(childs, i - 1))->next = ((t_ast_node *)get_dynarray_value(childs, i));
		((t_ast_node *)get_dynarray_value(childs, i))->parent = parent;
		i++;
	}
	parent->content = childs;
	parent->child_count = childs->count + 2;
}
