/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:18:49 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/16 17:23:24 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_ast.h"

/**
 * 
 * @brief Adds a child node to the parent node's content.
 * 
 * @param parent The parent node to which the child will be added.
 * @param child The child node to be added.
 * 
 * @note If the parent node has no children, it initializes a new dynamic array
 * to hold the child nodes. If the parent already has children,
 * it appends the child to the existing array.
 * 
 * @note child_count = 0 -> content = NULL
 * @note child_count = 1 -> content = char *
 * @note child_count = 2 + n -> content = t_dynarray * with n children
 * 
 * @return int Returns 1 on success, 0 on failure (malloc error).
 * 
*/
int	add_ast_child_primitive(t_ast *parent, t_ast *child)
{
	t_dynarray	*sub_cmd;
	t_ast		*last_child;

	if (parent->child_count == 0)
	{
		sub_cmd = init_dynarray_malloc(50,
					(void *(*)(void *))destroy_ast);
		if (!sub_cmd || !push(sub_cmd, child, FALSE))
			return (0);
		parent->content = sub_cmd;
		parent->child_count = 3;
		return (1);
	}
	if (!push(parent->content, child, FALSE))
		return (0);
	last_child = get_dynarray_value(parent->content, parent->child_count - 3);
	last_child->next = child;
	parent->child_count++;
	return (1);
}

/**
 * 
 * @brief Adds multiple child nodes to a parent node.
 * 
 * @param parent The parent node to which the child nodes will be added.
 * @param childs The dynamic array of child nodes to be added.
 * 
 * @note This function links the child nodes together by setting
 * 
*/
void	add_ast_childs(t_ast *parent, t_ast *childs)
{
	t_dynarray	*content;
	t_ast		*node;
	t_uint		i;

	i = 0;
	if (!childs)
	{
		destroy_ast(childs);
		return ;
	}
	content = childs->content;
	while (i < content->count)
	{
		if (i > 0)
		{
			node = get_dynarray_value(content, i - 1);
			node->next = get_dynarray_value(content, i);
		}
		node = get_dynarray_value(content, i);
		node->parent = parent;
		i++;
	}
	parent->content = content;
	parent->child_count = content->count + 2;
}
