#ifndef MAP_H
# define MAP_H

#include "types.h"
#include <stdlib.h>

//#include "libft.h"

typedef struct s_dynamic_array
{
	void	**data;
	t_uint	size;
	t_uint	count;
	void	*(*free_func)(void *);
}	t_dynamic_array;

//typedef struct s_pointer {
//    void    *value;
//    t_bool  is_dyn_allocated;
//}   t_pointer;

void			set_value(t_dynamic_array *arr, t_uint index, void *value);
void			*get_value(t_dynamic_array *arr, t_uint index);
void			*destroy_dynamic_array(t_dynamic_array *arr);
t_dynamic_array	init_dynamic_array(t_uint size, void *(*free_func)(void *));
#endif