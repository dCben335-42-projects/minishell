#include "ast.h"

/**
 * @brief Adds the child node to the contents of the parent node.
 * 
 * @note If the allocation fails, it sets the "has_malloc_error" boolean to true.
 * @param parent The parent node to which the child node will be added.
 * @param child The child node to be added.
 * @param args The arguments structure containing the malloc error flag.
 * @return void
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
