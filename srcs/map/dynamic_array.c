#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

t_dynamic_array	*create_array(int size)
{
	t_dynamic_array	*arr;

	arr = malloc(sizeof(t_dynamic_array));
	arr->data = calloc(size, sizeof(void *));
	arr->size = size;
	return (arr);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}

void	set_value(t_dynamic_array *arr, int index, void *value)
{
	int	new_size;
	int	i;

	if (index >= arr->size)
	{
		new_size = index * 2;
		arr->data = ft_realloc(arr->data, arr->size * sizeof(void *),
				new_size * sizeof(void *));
		i = arr->size;
		while (i < new_size)
		{
			arr->data[i] = 0;
			i++;
		}
		arr->size = new_size;
	}
	arr->data[index] = value;
}

void	*get_value(t_dynamic_array *arr, int index)
{
	if (index < arr->size)
		return (arr->data[index]);
	return (0);
}

void	free_array(t_dynamic_array *arr)
{
	free(arr->data);
	free(arr);
}

