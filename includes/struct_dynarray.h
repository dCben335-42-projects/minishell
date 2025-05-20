/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_dynarray.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:36:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 12:57:33 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_DYNARRAY_H
# define STRUCT_DYNARRAY_H

# include "types.h"
# include <stdlib.h>

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
void			*get_dynarray_value_last(t_dynarray *arr);

void			*destroy_dynarray(t_dynarray *arr);
void			*free_value(void *data);

#endif