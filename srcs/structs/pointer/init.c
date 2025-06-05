/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:40:46 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/05 20:41:03 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_pointer.h"

/**
 * @brief Initializes a pointer structure with the given pointer
 * and allocation status.
 * 
 * @param pointer The pointer to be initialized.
 * @param is_malloc Indicates if the pointer was allocated with malloc.
 * 
 * @note If the pointer is NULL and is_malloc is TRUE, the has_malloc_error
 * field will be set to TRUE. Otherwise, it will be set to FALSE.
 * 
 * @return t_ptr The initialized pointer structure.
 */
t_ptr	init_pointer(void *pointer, t_bool is_malloc)
{
	t_ptr	ptr;

	ptr.p = pointer;
	ptr.is_malloc = is_malloc;
	if (is_malloc && !pointer)
	{
		ptr.has_malloc_error = TRUE;
		return (ptr);
	}
	ptr.has_malloc_error = FALSE;
	return (ptr);
}
