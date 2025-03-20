#include "dynamic_array.h"
#include "libft.h"
#include <stdio.h>
#include "parser_lexer.h"

void	*ft_realloc(t_dynamic_array *arr, size_t new_size)
{
	void	**new_ptr;
	size_t	copy_size;

	if (!arr->data)
		return (malloc(new_size * sizeof(void *)));
	if (new_size == 0)
		return (destroy_dynamic_array(arr));
	new_ptr = malloc(new_size * sizeof(void *));
	if (!new_ptr)
		return (destroy_dynamic_array(arr));
	if (arr->size < new_size)
		copy_size = arr->size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, arr->data, copy_size * sizeof(void *));
	destroy_dynamic_array(arr);
	return (new_ptr);
}

void	set_value(t_dynamic_array *arr, t_uint index, void *value)
{
	t_uint	new_size;
	size_t	i;

	if (index >= arr->size)
	{
		new_size = arr->size * 2;
		arr->data = ft_realloc(arr, new_size);
		if (!arr->data)
		{
			arr->count = 0;
			arr->size = 0;
			return ;
		}

		i = arr->size;
		while (i < new_size)
		{
			arr->data[i] = 0;
			i++;
		}
		arr->size = new_size;
	}
	arr->count++;
	arr->data[index] = value;
}
