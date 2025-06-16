/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:47:55 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/16 14:19:22 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "config.h"

static t_dynarray	*push_tree_values(t_tree *tree, t_dynarray *arr)
{
	char	*value;

	if (!tree || !arr)
		return (NULL);
	push_tree_values(tree->left, arr);
	value = ft_strdup(tree->value);
	if (!value || !push(arr, value, TRUE))
	{
		free(value);
		return (NULL);
	}
	push_tree_values(tree->right, arr);
	return (arr);
}

static t_dynarray	*save_wildcard(
	t_shell *shell,
	t_dynarray *args,
	char *value)
{
	t_tree		*tree;
	t_dynarray	*ret;

	tree = expand_wildcard_word(shell, value);
	if (!tree)
		return (NULL);
	ret = push_tree_values(tree, args);
	destroy_tree(tree);
	return (ret);
}

/**
 * @brief Saves the expanded entry into the dynamic array of arguments.
 * 
 * @param shell The shell instance.
 * @param args The dynamic array of arguments to save the entry into.
 * @param value The value to be saved.
 * @param is_wildcard Indicates if the value is a wildcard.
 * 
 * @return A pointer to an empty string if successful, NULL otherwise.
 */
char	*save_expand(
	t_shell *shell,
	t_dynarray *args,
	char *value,
	t_bool is_wildcard
)
{
	const char	charset[] = {-SYMBOL_GLOB_ANY, -SYMBOL_GLOB_ONE, '\0'};

	if (is_wildcard && ft_strchr(value, -SYMBOL_GLOB_ANY))
	{
		if (!save_wildcard(shell, args, value))
			return (NULL);
	}
	else
	{
		ft_strpositivate(&value, charset);
		if (!push(args, value, TRUE))
		{
			free(value);
			return (NULL);
		}
	}
	return (ft_strdup(""));
}
