#include "node.h"

t_ast_node	*init_node(t_node_type type, char *value)
{
    t_ast_node *node = malloc(sizeof(t_ast_node));
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

void add_child(t_ast_node *parent, t_ast_node *child)
{
	t_dynamic_array	*sub_cmd;

	if (parent->child_count == 0)
	{
		sub_cmd = init_dynamic_array_malloc(40, NULL);
		set_value(sub_cmd, 0, child);
		parent->content = sub_cmd;
		parent->child_count = 2;
		return ;
	}
	set_value(parent->content, parent->child_count - 1, child);
	parent->child_count++;
}
