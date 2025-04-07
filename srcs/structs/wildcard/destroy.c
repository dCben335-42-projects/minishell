/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:58:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/07 21:36:01 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "dynarray.h"

void	*destroy_wildcard(t_wildcard *wildcard)
{
	free(wildcard->pattern);
	free(wildcard->prefix);
	free(wildcard->suffix);
	free(wildcard->base_path);
	destroy_dynarray(&wildcard->arr);
	wildcard->is_error = TRUE;
	return (NULL);
}