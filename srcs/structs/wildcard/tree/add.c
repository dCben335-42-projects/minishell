/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:27:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 05:45:47 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "libft_tree.h"

/**
 * @brief Adds a wildcard node to the tree.
 *
 * @param wildcard The wildcard structure to add.
 * @param node The tree node to add the wildcard to.
 * 
 * @return The new tree node with the wildcard added.
 */
t_tree	*add_wildcard_tree(t_wildcard *wildcard, t_tree *node)
{
	return (add_tree_node(&wildcard->tree, node));
}
