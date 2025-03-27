#include "dynamic_array.h"
#include "libft.h"

void	*destroy_dynarray(t_dynamic_array *arr)
{
	size_t	i;

	i = 0;
	if (arr->destroyer != NULL)
	{
		while (i < arr->size)
		{
			if (arr->data[i] != NULL)
				arr->destroyer(arr->data[i]);
			i++;
		}
	}
	free(arr->data);
	return (NULL);
}
