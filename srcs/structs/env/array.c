/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:35:42 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/06 18:42:19 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_dynarray.h"
#include "libft.h"
#include "struct_env.h"

char *stringify_env(t_env *env)
{
	const char	*strs[] = {env->key, "=", env->value};

	if (!env || !env->key || !env->value)
		return (NULL);
	return (ft_strsjoin(strs, 3, ""));
}

void	fill_env_array(t_env *env, t_dynarray *arr)
{
	char	*str;

	if (!env || !arr)
		return;
	fill_env_array(env->left, arr);
	str = stringify_env(env);
	if (str) 
		push(arr, str);
	fill_env_array(env->right, arr);
}

t_dynarray env_to_array(t_env *env)
{
	t_dynarray	arr;

	arr = init_dynarray(20, free_value);
	fill_env_array(env, &arr);
	return (arr);
}