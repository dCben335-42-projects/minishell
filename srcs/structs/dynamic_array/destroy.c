#include "map.h"
#include "libft.h"

void	destroy_dynamic_array(t_dynamic_array *arr, void (*free_func)(void *))
{
	size_t i;

	i = 0;
	if (free_func != NULL)
	{
		while (i < arr->size)
		{
			if (arr->data[i] != NULL)
				free_func(arr->data[i]);
			i++;
		}
	}
	free(arr->data);
	free(arr);
}
