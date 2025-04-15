/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:03:24 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 15:24:21 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdlib.h>

void	*destroy_env_node(t_env **env, t_env *node)
{
	return (destroy_tree_node(env, node));
}

void	*destroy_env(t_env *env)
{
	return (destroy_tree(env));
}
