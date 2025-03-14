#ifndef MAP_H
# define MAP_H

//#include "libft.h"

typedef struct s_dynamic_array
{
	void	**data;
	int		size;
}	t_dynamic_array;

//typedef struct s_pointer {
//    void    *value;
//    t_bool  is_dyn_allocated;
//}   t_pointer;

t_dynamic_array	*create_dynamic_array(int size);
void			set_value(t_dynamic_array *arr, int index, void *value);
void			*get_value(t_dynamic_array *arr, int index);
void			free_dynamic_array(t_dynamic_array *arr, void (*free_func)(void *));

#endif