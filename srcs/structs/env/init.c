/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:44:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 03:27:47 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_env.h"
#include "libft.h"

static void	*free_val(void *value)
{
	free(value);
	return (NULL);
}

static void	*free_node_params(char *key, char *value)
{
	free(key);
	free(value);
	return (NULL);
}

#include <stdio.h>

/**
 * @brief Initializes a new environment node with the given envp string.
 *
 * @param envp The environment variable string to parse.
 * 
 * @return A pointer to the initialized environment node, or NULL on failure.
 */
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
	node = init_tree_node(key, value, &ft_strcmp, &free_val);
	if (!node)
		return (free_node_params(key, value));
	return (node);
}

/**
 * @brief Initializes the environment with the given envp.
 *
 * @param envp The environment variables from the system.
 * 
 * @return The root of the environment tree.
 */
t_env	*init_env(char **envp)
{
	t_env	*env;
	size_t	i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		add_env_node(&env, init_env_node(envp[i]));
		i++;
	}
	return (env);
}
