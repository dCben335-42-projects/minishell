/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:46:46 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 17:47:00 by bcabocel         ###   ########.fr       */
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
	return (arr);
}
