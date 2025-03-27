#include "dynamic_array.h"
#include "libft.h"

t_dynamic_array	init_dynarray(t_uint size, void *(*destroyer)(void *))
{
	t_dynamic_array	arr;

	arr.data = ft_calloc(size + 1, sizeof(void *));
	arr.size = size;
	arr.count = 0;
	arr.destroyer = destroyer;
	return (arr);
}
