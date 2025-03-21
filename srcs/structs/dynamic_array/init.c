#include "dynamic_array.h"
#include "libft.h"

t_dynamic_array	init_dynamic_array(t_uint size, void *(*free_func)(void *))
{
	t_dynamic_array	arr;

	arr.data = ft_calloc(size, sizeof(void *));
	arr.size = size;
	arr.count = 0;
	arr.free_func = free_func;
	return (arr);
}

t_dynamic_array	*init_dynamic_array_malloc(t_uint size, void *(*free_func)(void *))
{
	t_dynamic_array	*arr;

	arr = malloc(sizeof(t_dynamic_array));
	arr->data = ft_calloc(size, sizeof(void *));
	arr->size = size;
	arr->count = 0;
	arr->free_func = free_func;
	return (arr);
}
