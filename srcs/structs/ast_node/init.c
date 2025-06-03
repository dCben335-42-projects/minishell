/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:02:31 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/03 18:29:05 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_node.h"

/**
 * 
 * @brief Initializes a new AST node with the given type and value.
 * 
 * @param type The type of the node to be initialized.
 * @param value The value to be assigned to the node.
 * 
 * @return t_ast_node* Pointer to the initialized node or NULL on malloc error.
 * 
*/
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

/**
 * 
 * @brief Initializes an AST node on the stack with the given type.
 * 
 * @param node Pointer to the AST node to be initialized.
 * @param type The type of the node to be initialized.
 * 
*/
void	init_node_on_stack(t_ast_node *node, t_node_type type)
{
	node->type = type;
	node->parent = NULL;
	node->next = NULL;
	node->content = NULL;
	node->child_count = 0;
}

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
int	add_child_primitive(t_ast_node *parent, t_ast_node *child)
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
	((t_ast_node *)get_dynarray_value(parent->content, parent->child_count - 3))
	->next = child;
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
void	add_childs(t_ast_node *parent, t_dynarray *childs)
{
	t_uint	i;

	i = 0;
	while (i < childs->count)
	{
		if (i > 0)
			((t_ast_node *)get_dynarray_value(childs, i - 1))->next
			= ((t_ast_node *)get_dynarray_value(childs, i));
		((t_ast_node *)get_dynarray_value(childs, i))->parent = parent;
		i++;
	}
	parent->content = childs;
	parent->child_count = childs->count + 2;
}
