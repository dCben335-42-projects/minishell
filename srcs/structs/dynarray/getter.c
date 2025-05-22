/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:47:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 18:28:59 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_dynarray.h"

void	*get_dynarray_value(t_dynarray *arr, t_uint index)
{
	if (index < arr->size)
		return (arr->data[index]);
	return (0);
}

void	*get_dynarray_last_value(t_dynarray *arr)
{
	if (arr->count > 0)
		return (arr->data[arr->count - 1]);
	return (0);
}
