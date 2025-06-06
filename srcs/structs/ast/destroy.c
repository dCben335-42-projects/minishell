/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:04:40 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/06 03:10:23 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_dynarray.h"
#include "struct_ast.h"

/**
 * 
 * @brief Destroys a single AST node.
 * 
 * @param node The AST node to be destroyed.
 * 
 * @return NULL
 * 
*/
static void	*destroy_ast_node(t_ast *node)
{
	free(node->content);
	free(node);
	return (NULL);
}

/**
 * 
 * @brief Recursively destroys an AST node and its children.
 * 
 * @param node The AST node to be destroyed.
 * 
 * @return NULL
 * 
*/
void	*destroy_ast(t_ast *node)
{
	if (node == NULL)
		return (NULL);
	if (node->child_count == 1)
		return (destroy_ast_node(node));
	if (node->child_count > 1)
	{
		destroy_dynarray(node->content);
		free(node);
		return (NULL);
	}
	return (destroy_ast_node(node));
}
