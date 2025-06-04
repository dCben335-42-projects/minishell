/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:46:29 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 18:13:40 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_dynarray.h"
#include "libft.h"
#include <stdio.h>

/**
 * 
 * @brief Reallocates the dynamic array to a new size.
 * 
 * @param arr The dynamic array to be reallocated.
 * @param new_size The new size for the dynamic array.
 * 
 * @return A pointer to the new data array, or NULL if memory allocation fails.
 * 
*/
static void	**realloc_dynarray(t_dynarray *arr, size_t new_size)
{
	void	**new;
	size_t	copy_size;

	new = ft_calloc((new_size + 1), sizeof(void *));
	if (!new)
	{
		arr->count = 0;
		arr->size = 0;
		return (destroy_dynarray(arr));
	}
	if (arr->data)
	{
		if (new_size < arr->size)
			copy_size = new_size;
		else
			copy_size = arr->size;
		ft_memcpy(new, arr->data, copy_size * sizeof(void *));
		free(arr->data);
	}
	return (new);
}

/**
 * 
 * @brief Sets a value at the specified index in the dynamic array.
 * 
 * @param arr The dynamic array in which to set the value.
 * @param index The index at which to set the value.
 * @param value The value to set at the specified index.
 * 
 * @return A pointer to the value set at the specified index
 * or NULL if memory allocation fails.
 * 
 */
void	*set_dynarray_value(t_dynarray *arr, t_uint index, void *value)
{
	t_uint	new_size;
	
	if (index >= arr->size)
	{
		new_size = arr->size * 2;
		arr->data = realloc_dynarray(arr, new_size);
		if (!arr->data)
			return (NULL);
		arr->size = new_size;
	}
	arr->count++;
	arr->data[index] = value;
	if (index > (long)arr->last_index - 1)
		arr->last_index = index + 1;
	return (arr->data[index]);
}

/**
 * 
 * @brief Pushes a value onto the dynamic array.
 * 
 * @param arr The dynamic array to which the value will be pushed.
 * @param value The value to be pushed onto the dynamic array.
 * 
 * @note This function sets the new value behind the last index
 * and increments the last index.
 * 
 * @return A pointer to the pushed value, or NULL if memory allocation fails.
 * 
*/
void	*push(t_dynarray *arr, void *value)
{
	set_dynarray_value(arr, arr->last_index, value);
	if (!arr->data)
		return (NULL);
	return (arr->data[arr->last_index - 1]);
}
