/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:45:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/14 01:16:09 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

t_env	*add_existing_env(t_env *env, char *key, char *value)
{
	t_env	*matched_env;
	
	matched_env = get_env_node(env, key);
	if (!matched_env)
		return (NULL);
	free(matched_env->value);
	matched_env->value = value;
	return (matched_env);
}

t_env	*add_env(t_env **env, t_env *new)
{
    if (!new)
        return (NULL);
    if (!*env)
    {
        *env = new;
        return (new);
    }
    if (ft_strcmp(new->key, (*env)->key) < 0)
		return (add_env(&(*env)->left, new));
	return (add_env(&(*env)->right, new));
}
