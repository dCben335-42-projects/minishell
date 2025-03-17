//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "map.h"
//#include "types.h"
//#include "libft.h"
//#include "parser_lexer.h"

//t_dynamic_array	*create_dynamic_array(t_uint size)
//{
//	t_dynamic_array	*arr;

//	arr = malloc(sizeof(t_dynamic_array));
//	arr->data = ft_calloc(size, sizeof(void *));
//	arr->size = size;
//	arr->count = 0;
//	return (arr);
//}

//void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
//{
//	void	*new_ptr;
//	size_t	copy_size;

//	if (!ptr)
//		return (malloc(new_size));
//	if (new_size == 0)
//	{
//		free(ptr);
//		return (NULL);
//	}
//	new_ptr = malloc(new_size);
//	if (!new_ptr)
//		return (NULL);
//	if (ptr)
//	{
//		if (old_size < new_size)
//			copy_size = old_size;
//		else
//			copy_size = new_size;
//		ft_memcpy(new_ptr, ptr, copy_size);
//		free(ptr);
//	}
//	return (new_ptr);
//}

//void	set_value(t_dynamic_array *arr, t_uint index, void *value)
//{
//	t_uint	new_size;
//	t_uint	new_count;
//	size_t	i;

//	if (index >= arr->size)
//	{
//		new_size = arr->size * 2;
//		new_count = arr->count + 1;
//		arr->data = ft_realloc(arr->data, arr->size * sizeof(void *),
//				new_size * sizeof(void *));
//		i = arr->size;
//		while (i < new_size)
//		{
//			arr->data[i] = 0;
//			i++;
//		}
//		arr->size = new_size;
//		arr->count = new_count;
//	}
//	else
//		arr->count++;
//	arr->data[index] = value;
//}

//void	*get_value(t_dynamic_array *arr, t_uint index)
//{
//	if (index < arr->size)
//		return (arr->data[index]);
//	return (0);
//}

//void	free_dynamic_array(t_dynamic_array *arr, void (*free_func)(void *))
//{
//	size_t i;

//	i = 0;
//	if (free_func != NULL)
//	{
//		while (i < arr->size)
//		{
//			if (arr->data[i] != NULL) {
//				free_func(arr->data[i]);
//				//free(arr->data[i]);
//			}
//			i++;
//		}
//	}
//	free(arr->data);
//	free(arr);
//}
