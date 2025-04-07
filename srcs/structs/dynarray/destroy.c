#include "dynarray.h"
#include "libft.h"

void	*basic_destroyer(void *data)
{
	free(data);
	return (NULL);
}

void	*destroy_dynarray(t_dynarray *arr)
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
