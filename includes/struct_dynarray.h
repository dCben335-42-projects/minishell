/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_dynarray.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:36:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 18:18:02 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_DYNARRAY_H
# define STRUCT_DYNARRAY_H

# include "types.h"
# include <stdlib.h>

/**
 * 
 * @brief A dynamic array structure that can hold pointers to any type of data.
 * 
 * @param data A pointer to an array of pointers, which can hold
 * any type of data.
 * @param size The current allocated size of the dynamic array.
 * @param count The current number of elements in the dynamic array.
 * @param last_index The index of the last element.
 * @param destroyer A function pointer to a destroyer function
 * that will be used for freeing the contents of the array.
 * @param is_malloc A boolean indicating if the dynamic array
 * was allocated with malloc.
 * 
 * @note The `data` field is a pointer to an array of pointers, allowing
 * for dynamic resizing and storage of any type of data.
 * 
*/
typedef struct s_dynarray
{
	void	**data;
	t_uint	size;
	t_uint	count;
	t_uint	last_index;
	void	*(*destroyer)(void *);
	t_bool	is_malloc;
}	t_dynarray;

t_dynarray		init_dynarray(t_uint size, void *(*destroyer)(void *));
t_dynarray		*init_dynarray_malloc(t_uint size, void *(*destroyer)(void *));

void			*set_dynarray_value(t_dynarray *arr, t_uint index, void *value);
void			*push(t_dynarray *arr, void *value);

void			*get_dynarray_value(t_dynarray *arr, t_uint index);
void			*get_dynarray_last_value(t_dynarray *arr);

void			*destroy_dynarray(t_dynarray *arr);
void			*free_value(void *data);

#endif