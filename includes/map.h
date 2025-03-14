#ifndef MAP_H
# define MAP_H

typedef struct s_dynamic_array
{
	void	**data;
	int		size;
}	t_dynamic_array;

t_dynamic_array	*create_array(int size);
void	set_value(t_dynamic_array *arr, int index, void *value);
void	*get_value(t_dynamic_array *arr, int index);

#endif