/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:44:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 19:23:02 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static void	*free_val(char *key)
{
	free(key);
	return (NULL);
}

t_env	*init_env_node(char *envp)
{
	t_env	*node;
	char	*key;
	char	*value;
	
	key = parse_env_key(envp);
	value = parse_env_value(envp);
	if (!value)
		value = ft_strdup("");
	node = init_tree_node(key, value, FALSE,\
		(void * (*)(void *))&free_val);
	if (!node)
	{
		free(key);
		free(value);
		return (NULL);
	}
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
