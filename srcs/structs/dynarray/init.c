/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:46:46 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 18:13:50 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_dynarray.h"
#include "libft.h"

/**
 * 
 * @brief Initializes a dynamic array with the specified size
 * and destroyer function. 
 * 
 * @param size The initial size of the dynamic array.
 * @param destroyer A function pointer to a destroyer function
 * 
 * @return A t_dynarray structure initialized with the given size.
 * 
*/
t_dynarray	init_dynarray(t_uint size, void *(*destroyer)(void *))
{
	t_dynarray	arr;

	arr.data = ft_calloc(size + 1, sizeof(void *));
	arr.size = size;
	arr.count = 0;
	arr.last_index = 0;
	arr.destroyer = destroyer;
	arr.is_malloc = FALSE;
	return (arr);
}

/**
 * 
 * @brief Initializes a dynamic array with the specified size
 * 
 * @param size The initial size of the dynamic array.
 * @param destroyer A function pointer to a destroyer function
 * 
 * @return A pointer to a t_dynarray structure initialized with the given size,
 * or NULL if memory allocation fails.
 * 
*/
t_dynarray	*init_dynarray_malloc(t_uint size, void *(*destroyer)(void *))
{
	t_dynarray	*arr;

	arr = malloc(sizeof(t_dynarray));
	if (!arr)
		return (NULL);
	arr->data = ft_calloc(size + 1, sizeof(void *));
	if (!arr->data)
	{
		free(arr);
		return (NULL);
	}
	arr->size = size;
	arr->count = 0;
	arr->last_index = 0;
	arr->destroyer = destroyer;
	arr->is_malloc = TRUE;
	return (arr);
}
