/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_dynarray.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:36:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 19:12:07 by bcabocel         ###   ########.fr       */
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
	void	*(*destroyer)(void *);
}	t_dynarray;

void			set_dynarray_value(t_dynarray *arr, t_uint index, void *value);
void			*get_dynarray_value(t_dynarray *arr, t_uint index);
void			*destroy_dynarray(t_dynarray *arr);
t_dynarray		init_dynarray(t_uint size, void *(*destroyer)(void *));
void			*free_value(void *data);

#endif