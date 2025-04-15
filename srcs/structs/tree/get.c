/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:44:49 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 15:08:37 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_tree.h"
#include "libft.h"

size_t	get_size_tree(t_tree *tree)
{
	if (!tree)
		return (0);
	return (1 + get_size_tree(tree->left) + get_size_tree(tree->right));
}

t_tree	*get_tree_parent(t_tree *tree, t_tree *node)
{
	t_tree	*parent;

	if (!tree || !node)
		return (NULL);
	if (tree->left == node || tree->right == node)
		return (tree);
	parent = get_tree_parent(tree->left, node);
	if (parent)
		return (parent);
	return (get_tree_parent(tree->right, node));
}

t_tree	*get_tree_node(t_tree *tree, char *key)
{
	if (!tree || !key)
		return (NULL);
	if (ft_strcmp(key, tree->key) == 0)
		return (tree);
	if (ft_strcmp(key, tree->key) < 0)
		return (get_tree_node(tree->left, key));
	return (get_tree_node(tree->right, key));
}