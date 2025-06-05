/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:47:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 17:58:58 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_dynarray.h"

/**
 * 
 * @brief Gets the value at the specified index in the dynamic array.
 * 
 * @param arr The dynamic array from which to get the value.
 * @param index The index of the value to get.
 * 
 * @return The value at the specified index, or NULL
 * if the index is out of bounds.
 * 
 */
void	*get_dynarray_value(t_dynarray *arr, t_uint index)
{
	if (index < arr->size)
		return (arr->data[index]);
	return (0);
}

/**
 * 
 * @brief Gets the last value in the dynamic array.
 * 
 * @param arr The dynamic array from which to get the last value.
 * 
 * @return The last value in the dynamic array, or NULL
 * if the array is empty.
 * 
*/
void	*get_dynarray_last_value(t_dynarray *arr)
{
	if (arr->count > 0)
		return (arr->data[arr->count - 1]);
	return (0);
}
