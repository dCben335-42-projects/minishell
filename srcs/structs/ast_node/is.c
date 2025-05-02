#include "ast_node.h"

int	is_node(t_ast_node *node, size_t mask)
{
	return (node->type & mask);
}