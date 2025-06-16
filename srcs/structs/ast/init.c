/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:02:31 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/16 03:38:16 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_ast.h"

/**
 * 
 * @brief Initializes an AST node on the stack with the given type.
 * 
 * @param node Pointer to the AST node to be initialized.
 * @param type The type of the node to be initialized.
 * 
*/
void	reset_ast_node(t_ast *node, t_node_type type)
{
	node->type = type;
	node->parent = NULL;
	node->next = NULL;
	node->content = NULL;
	node->child_count = 0;
}

/**
 * 
 * @brief Initializes a new AST node with the given type and value.
 * 
 * @param type The type of the node to be initialized.
 * @param value The value to be assigned to the node.
 * 
 * @return t_ast* Pointer to the initialized node or NULL on malloc error.
 * 
*/
t_ast	*init_ast_node(t_node_type type, char *value)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->parent = NULL;
	node->next = NULL;
	node->content = NULL;
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
	node->child_count = 0;
	return (node);
}
