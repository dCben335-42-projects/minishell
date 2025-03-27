#include "dynamic_array.h"
#include "libft.h"
#include <stdio.h>
#include "parser_lexer.h"

static void	**ft_realloc(t_dynamic_array *arr, size_t new_size)
{
	void	**new;
	size_t	copy_size;

	new = ft_calloc((new_size + 1), sizeof(void *));
	if (!new)
	{
		arr->count = 0;
		arr->size = 0;
		return (destroy_dynamic_array(arr));
	}
	if (arr->data)
	{
		if (new_size < arr->size)
			copy_size = new_size;
		else
			copy_size = arr->size;
		ft_memcpy(new, arr->data, copy_size * sizeof(void *));
		free(arr->data);
	}
	return (new);
}

void	set_value(t_dynamic_array *arr, t_uint index, void *value)
{
	t_uint	new_size;

	if (index >= arr->size)
	{
		new_size = arr->size * 2;
		arr->data = ft_realloc(arr, new_size);
		if (!arr->data)
			return ;
		arr->size = new_size;
	}
	arr->count++;
	arr->data[index] = value;
}
