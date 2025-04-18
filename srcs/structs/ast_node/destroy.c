#include "dynamic_array.h"
#include "libft.h"
#include "node.h"

void	*destroy_node(t_ast_node *node)
{
	free(node->content);
	free(node);
	return (NULL);
}

void	*recursive_destroy_node(t_ast_node *node)
{
	if (node == NULL)
		return (NULL);
	if (node->child_count == 1)
		return (destroy_node(node));
	if (node->child_count > 1)
	{
		destroy_dynamic_array(node->content);
		free(node);
		return (NULL);
	}
	return (destroy_node(node));
}
