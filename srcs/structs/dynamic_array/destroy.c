#include "dynamic_array.h"
#include "libft.h"

void	*destroy_dynamic_array(t_dynamic_array *arr)
{
	size_t	i;

	i = 0;
	if (arr->free_func != NULL)
	{
		while (i < arr->size)
		{
			if (arr->data[i] != NULL)
				arr->free_func(arr->data[i]);
			i++;
		}
	}
	free(arr->data);
	if (arr->is_malloc == TRUE)
		free(arr);
	return (NULL);
}
