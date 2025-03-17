#include "map.h"
#include "libft.h"

void	*get_value(t_dynamic_array *arr, t_uint index)
{
	if (index < arr->size)
		return (arr->data[index]);
	return (0);
}
