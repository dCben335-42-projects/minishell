#include "map.h"
#include "libft.h"

void	*ft_realloc(t_dynamic_array *arr, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!arr->data)
		return (malloc(new_size));
	if (new_size == 0)
		return (destroy_dynamic_array(arr));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (destroy_dynamic_array(arr));
	if (arr->size < new_size)
		copy_size = arr->size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, arr->data, copy_size);
	destroy_dynamic_array(arr);
	return (new_ptr);
}

void	set_value(t_dynamic_array *arr, t_uint index, void *value)
{
	t_uint	new_size;
	t_uint	new_count;
	size_t	i;

	if (index >= arr->size)
	{
		new_size = arr->size * 2;
		new_count = arr->count + 1;
		arr->data = ft_realloc(arr, new_size * sizeof(void *));
		i = arr->size;
		while (i < new_size)
		{
			arr->data[i] = 0;
			i++;
		}
		arr->size = new_size;
		arr->count = new_count;
	}
	else
		arr->count++;
	arr->data[index] = value;
}
