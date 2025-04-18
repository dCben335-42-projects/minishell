/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:34:12 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 17:40:04 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_env.h"

size_t	get_size_env(t_env *env)
{
	return (get_size_tree(env));
}

t_env	*get_env_node(t_env *env, char *key)
{
	return (get_tree_node(env, key));
}
