/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:44:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/16 00:32:08 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static void	*free_val(char *value)
{
	free(value);
	return (NULL);
}

static void *free_node_params(char *key, char *value)
{
	free(key);
	free(value);
	return (NULL);
}

t_env	*init_env_node(char *envp)
{
	t_env	*node;
	char	*key;
	char	*value;
	
	key = parse_env_key(envp);
	if (!key || !ft_strcmp(key, "_"))
		return (free_node_params(key, NULL));
	value = parse_env_value(envp);
	if (!value && ft_strchr(envp, '='))
	{
		value = ft_strdup("");
		if (!value)
			return (free_node_params(key, NULL));
	}
	node = init_tree_node(key, value, &ft_strcmp,
		(void * (*)(void *))&free_val);
	if (!node)
		return (free_node_params(key, value));
	return (node);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	size_t	i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		add_env_node(&env, init_env_node(envp[i]));
		i++;
	}
	return (env);
}
