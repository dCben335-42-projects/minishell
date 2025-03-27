/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:34:12 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/27 19:12:54 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

size_t	get_size_env(t_env *env)
{
	if (!env)
		return (0);
	return (get_size_env(env->left) + 1 + get_size_env(env->right));
}

t_env	*get_parent_node(t_env *env, t_env *node)
{
	t_env	*parent;

	if (!env || !node)
		return (NULL);
	if (env->left == node || env->right == node)
		return (env);
	parent = get_parent_node(env->left, node);
	if (parent)
		return (parent);
	return (get_parent_node(env->right, node));
}

t_env	*get_env_node(t_env *env, char *key)
{
	if (!env || !key)
		return (NULL);
	if (ft_strcmp(key, env->key) == 0)
		return (env);
	if (ft_strcmp(key, env->key) < 0)
		return (get_env_node(env->left, key));
	return (get_env_node(env->right, key));
}
