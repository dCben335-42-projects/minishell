/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:04:57 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/06 03:10:23 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_ast.h"

/**
 * 
 * @brief Checks if the given node matches the specified mask.
 * 
 * @param node Pointer to the AST node to check.
 * @param mask The bitmask to check against the node's type.
 * 
 * @return integer > 0 if the node's type matches the mask, 0 otherwise.
 * 
*/
int	is_ast_types(t_ast *node, size_t mask)
{
	return (node->type & mask);
}

/**
 * 
 * @brief Checks if the given node is a wildcard node.
 * 
 * @param node Pointer to the AST node to check.
 * 
 * @return integer > 0 if the node is a wildcard node, 0 otherwise.
 * 
*/
int	is_ast_wildcard(t_ast *node)
{
	return (is_ast_types(node, CMD_WILDCARD | CMD_EXPAND));
}
