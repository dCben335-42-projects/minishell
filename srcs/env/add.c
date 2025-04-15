/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:45:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 19:23:02 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

t_env	*add_existing_env(t_env *env, char *key, char *value)
{
	return (add_existing_tree(env, key, value));
}

t_env	(*add_existing_env_ptr)(t_env *, char *, char *) = &add_existing_env_ptr;

t_env	*add_env_node(t_env **env, t_env *new)
{
	return (add_tree_node(env, new));
}
