/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:38:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/13 19:18:50 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

void	read_env(t_env *env, const char *prefix)
{
	if (!env)
		return ;
	read_env(env->left, prefix);
	if (prefix)
		printf("%s", prefix);
	printf("%s=%s\n", env->key, env->value);
	read_env(env->right, prefix);
}
