/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:42:22 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 14:56:54 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_tree.h"
#include "libft.h"

t_tree	*add_existing_tree(t_tree *tree, char *key, void *value)
{
	t_tree	*matched;
	
	matched = get_tree_node(tree, key);
	if (!matched)
		return (NULL);
	if (matched->value_destroyer)
		matched->value_destroyer(matched->value);
	free(matched->value);
	matched->value = value;
	return (matched);
}

t_tree	*add_tree_node(t_tree **tree, t_tree *new)
{
	if (!new)
		return (NULL);
	if (!*tree)
	{
		*tree = new;
		return (new);
	}
	if (ft_strcmp(new->key, (*tree)->key) < 0)
		return (add_tree_node(&(*tree)->left, new));
	return (add_tree_node(&(*tree)->right, new));
}
