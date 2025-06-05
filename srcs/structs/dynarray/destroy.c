/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:48:55 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/06 01:35:42 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_dynarray.h"
#include "libft.h"

/**
 * 
 * @brief Frees the value then returns NULL.
 * 
 * @param data The data to be freed.
 * 
 * @return NULL
 * 
*/
void	*free_value(void *data)
{
	free(data);
	return (NULL);
}

/**
 * 
 * @brief Destroys a dynamic array and its contents.
 * 
 * @param arr The dynamic array to be destroyed.
 * 
 * @note Use the destroyer function to free the contents of the array.
 * 
 * @return NULL
 * 
*/
void	*destroy_dynarray(t_dynarray *arr)
{
	size_t	i;

	i = 0;
	if (arr->destroyer)
	{
		while (i < arr->size)
		{
			if (arr->data[i])
				arr->destroyer(arr->data[i]);
			i++;
		}
	}
	free(arr->data);
	if (arr->is_malloc)
	{
		free(arr);
		arr = NULL;
	}
	return (NULL);
}
