/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:47:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 17:47:10 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_dynarray.h"

void	*get_dynarray_value(t_dynarray *arr, t_uint index)
{
	if (index < arr->size)
		return (arr->data[index]);
	return (0);
}
