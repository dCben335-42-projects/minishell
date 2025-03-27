#ifndef MAP_H
# define MAP_H

# include "types.h"
# include <stdlib.h>

typedef struct s_dynarray
{
	void	**data;
	t_uint	size;
	t_uint	count;
	void	*(*destroyer)(void *);
}	t_dynamic_array;

void			set_dynarray_value(t_dynamic_array *arr, t_uint index, void *value);
void			*get_dynarray_value(t_dynamic_array *arr, t_uint index);
void			*destroy_dynarray(t_dynamic_array *arr);
t_dynamic_array	init_dynarray(t_uint size, void *(*destroyer)(void *));
#endif