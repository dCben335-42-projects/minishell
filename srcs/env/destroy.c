/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:03:24 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/13 19:21:32 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

static void	*free_env_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
	return (NULL);
}

static void	bind_rightmost(t_env *replacement, t_env *right_subtree)
{
	t_env	*temp;

	if (!replacement || !right_subtree || right_subtree == replacement)
		return ;
	temp = replacement;
	while (temp->right)
		temp = temp->right;
	temp->right = right_subtree;
}

void	*destroy_env_node(t_env **env, t_env *node)
{
	t_env	*replacement;
	t_env	*parent;

	if (!env || !node)
		return (NULL);
	parent = get_parent_node(*env, node);
	if (node->left)
		replacement = node->left;
	else
		replacement = node->right;
	if (!parent)
		*env = replacement;
	else if (parent->left == node)
		parent->left = replacement;
	else
		parent->right = replacement;
	bind_rightmost(replacement, node->right);
	free_env_node(node);
	return (NULL);
}

void	*destroy_env(t_env *env)
{
	if (!env)
		return (NULL);
	destroy_env(env->left);
	destroy_env(env->right);
	free_env_node(env);
	return (NULL);
}
