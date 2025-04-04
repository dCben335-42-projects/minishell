#ifndef MAP_H
# define MAP_H

# include "types.h"
# include <stdlib.h>

typedef struct s_dynamic_array
{
	void	**data;
	t_uint	size;
	t_uint	count;
	void	*(*free_func)(void *);
	t_bool	is_malloc;
}	t_dynamic_array;

void			set_value(t_dynamic_array *arr, t_uint index, void *value);
void			*get_value(t_dynamic_array *arr, t_uint index);
void			*destroy_dynamic_array(t_dynamic_array *arr);
t_dynamic_array	init_dynamic_array(t_uint size, void *(*free_func)(void *));
t_dynamic_array	*init_dynamic_array_malloc(t_uint size, void *(*free_func)(void *));
void			*destroy_dynamic_array_malloc(t_dynamic_array *arr);

#endif