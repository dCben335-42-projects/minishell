/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:47:55 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/28 15:19:19 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"

static t_dynarray	*push_tree_values(t_tree *tree, t_dynarray *arr)
{
	char	*value;

	if (!tree || !arr)
		return (NULL);
	push_tree_values(tree->left, arr);
	value = ft_strdup(tree->value);
	if (!value || !push(arr, value))
	{
		free(value);
		return (NULL);
	}
	push_tree_values(tree->right, arr);
	return (arr);
}

static t_dynarray	*save_wildcard(t_shell *shell, t_dynarray *args, char *value)
{
	t_tree	*tree;
	t_dynarray	*ret;

	tree = expand_wildcard_word(shell, value);
	if (!tree)
		return (NULL);
	ret = push_tree_values(tree, args);
	destroy_tree(tree);
	return (ret);
}

char	*save_expand_entry(t_shell *shell, t_dynarray *args, char *value, t_bool *is_wildcard)
{
	if (*is_wildcard)
	{
		if (!save_wildcard(shell, args, value))
			return (NULL);
	}
	else if (!push(args, value))
		return (NULL);
	*is_wildcard = FALSE;
	return (ft_strdup(""));
}