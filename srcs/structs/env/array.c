/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:35:42 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/16 18:05:13 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_dynarray.h"
#include "libft.h"
#include "struct_env.h"
#include <stdio.h>

static char	*stringify_env(t_env *env)
{
	const char	*strs[] = {env->key, "=", env->value};

	if (!env || !env->key || !env->value)
		return (NULL);
	return (ft_strsjoin(strs, 3, ""));
}

static void	*fill_env_array(t_env *env, t_dynarray *arr)
{
	char	*str;

	if (!env || !arr)
		return (arr);
	if (!fill_env_array(env->left, arr))
		return (NULL);
	str = stringify_env(env);
	if (str && !push(arr, str, TRUE))
	{
		free(str);
		return (NULL);
	}
	return (fill_env_array(env->right, arr));
}

/**
 * 
 * @brief Converts the environment tree into a dynamic array.
 *
 * This function initializes a dynamic array and fills it with the
 * string representations of the environment variables stored in the
 * binary tree structure.
 *
 * @param env The environment tree to convert.
 * 
 * @return A dynamic array containing the environment variables as strings.
 * 
 */
t_dynarray	env_to_array(t_env *env)
{
	t_dynarray	arr;

	arr = init_dynarray(100, free_value);
	if (!arr.data || !fill_env_array(env, &arr))
		printf("exec env could be created\n");
	return (arr);
}
