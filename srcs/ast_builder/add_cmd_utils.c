#include "ast.h"

/**
 * 
 * @brief Adds the child node to the contents of the parent node.
 * 
 * @param parent The parent node to which the child node will be added.
 * @param child The child node to be added.
 * @param args The arguments structure containing the malloc error flag.
 * 
 * @note If the allocation fails, it sets the "has_malloc_error" boolean to true.
 *
*/
void	add_child(t_ast_node *parent,
	t_ast_node **child, t_get_cmd_master *args)
{
	if (*child)
	{
		if (!add_child_primitive(parent, *child))
		{
			args->has_malloc_error = TRUE;
			return ;
		}
		*child = NULL;
	}
}
