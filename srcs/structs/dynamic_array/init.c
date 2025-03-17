#include "map.h"
#include "libft.h"

t_dynamic_array	*init_dynamic_array(t_uint size)
{
	t_dynamic_array	*arr;

	arr = malloc(sizeof(t_dynamic_array));
	arr->data = ft_calloc(size, sizeof(void *));
	arr->size = size;
	arr->count = 0;
	return (arr);
}
