/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:24:51 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 14:58:54 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_tree.h"
#include "libft.h"

t_tree	*init_tree_node(
	char *key,
	void *value,
	t_bool is_nullish_value,
	void *(*value_destroyer)(void *)
)
{
	t_tree	*node;

	if (is_nullish_value && !key)
		return (NULL);
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	node->value = value;
	node->value_destroyer = value_destroyer;
	return (node);
}
