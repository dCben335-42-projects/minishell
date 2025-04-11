/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:58:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/11 20:31:20 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "dynarray.h"
#include "libft.h"

void    *nullify_wildcard(t_wildcard *wildcard)
{
	wildcard->is_prefix = FALSE;
	wildcard->is_suffix = FALSE;
	wildcard->is_dir = FALSE;
	wildcard->pattern = NULL;
	wildcard->prefix = NULL;
	wildcard->suffix = NULL;
	wildcard->base_path = NULL;
	wildcard->arr.data = NULL;
	return (NULL);
}

void	*destroy_wildcard(t_wildcard *wildcard)
{
	free(wildcard->pattern);
	free(wildcard->prefix);
	free(wildcard->suffix);
	free(wildcard->base_path);
	destroy_dynarray(&wildcard->arr);
	return (nullify_wildcard(wildcard));
}