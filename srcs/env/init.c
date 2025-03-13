/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:44:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/13 19:08:27 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

static void	*free_init_error(char *key, char *value)
{
	free(key);
	free(value);
	return (NULL);
}

t_env	*init_env_node(char *envp)
{
	t_env	*new;
	char	*key;
	char	*value;

	key = parse_env_key(envp);
	value = parse_env_value(envp);
	if (!key || !value)
		return (free_init_error(key, value));
	new = malloc(sizeof(t_env));
	if (!new)
		return (free_init_error(key, value));
	new->key = key;
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	size_t	i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		add_env(&env, init_env_node(envp[i]));
		i++;
	}
	return (env);
}
