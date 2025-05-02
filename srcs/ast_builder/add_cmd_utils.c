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

/**
 * @brief Adds child node array to parent content and increments the index of "count + 1".
 * @param cmd_master The parent node to which the child nodes will be added.
 * @param sub_cmd The child node array to be added.
 * @param i The index to be incremented.
 * @param count The number of child nodes to be added.
 * @return void
 */
void	add_childs_and_increment(t_ast_node *cmd_master,
	t_dynarray *sub_cmd, t_uint *i, int count)
{
	add_childs(cmd_master, sub_cmd);
	*i += count + 1;
}
