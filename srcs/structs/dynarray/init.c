/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:46:46 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 21:01:16 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_dynarray.h"
#include "libft.h"

t_dynarray	init_dynarray(t_uint size, void *(*destroyer)(void *))
{
	t_dynarray	arr;

	arr.data = ft_calloc(size + 1, sizeof(void *));
	arr.size = size;
	arr.count = 0;
	arr.destroyer = destroyer;
	arr.is_malloc = FALSE;
	return (arr);
}

t_dynarray	*init_dynarray_malloc(t_uint size, void *(*destroyer)(void *))
{
	t_dynarray	*arr;

	arr = malloc(sizeof(t_dynarray));
	if (!arr)
		return (NULL);
	arr->data = ft_calloc(size + 1, sizeof(void *));
	if (!arr->data)
	{
		free(arr);
		return (NULL);
	}
	arr->size = size;
	arr->count = 0;
	arr->destroyer = destroyer;
	arr->is_malloc = TRUE;
	return (arr);
}
