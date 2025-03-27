#include "dynarray.h"
#include "libft.h"

void	*get_dynarray_value(t_dynarray *arr, t_uint index)
{
	if (index < arr->size)
		return (arr->data[index]);
	return (0);
}
