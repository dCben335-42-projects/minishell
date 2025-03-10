/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:38:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/10 15:41:39 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

void	read_env(t_env *env, const char *prefix)
{
	while (env)
	{
		if (prefix)
			printf("%s%s=%s\n", prefix, env->key, env->value);
		else
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}