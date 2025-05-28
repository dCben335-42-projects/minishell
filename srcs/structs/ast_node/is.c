#include "ast_node.h"

int	is_node(t_ast_node *node, size_t mask)
{
	return (node->type & mask);
}

int	is_node_wildcard(t_ast_node *node)
{
	return (is_node(node, CMD_WILDCARD | CMD_EXPAND));
}