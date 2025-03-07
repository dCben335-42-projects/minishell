/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:44:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/07 16:30:34 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

t_env	*init_env(char *envp)
{
	t_env	*new;
	char	*key;
	char	*value;

	key = get_key_from_envp(envp);
	value = get_value_from_envp(envp);
	if (!key || !value)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*create_envs(char **envp)
{
	t_env	*env;
	size_t	i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		add_env(&env, init_env(envp[i]));
		i++;
	}
	return (env);
}