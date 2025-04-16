/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:58:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/16 20:15:24 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "dynarray.h"
#include "libft.h"

/**
 * @brief Destroys the wildcard structure and frees its allocated memory.
 * 
 * @param wildcard The wildcard structure to destroy.
 * @return NULL
 * 
 * This function frees all the dynamically allocated memory associated with
 * the wildcard structure, including the pattern, prefix, suffix, base path,
 * and the tree.
 * 
 * @note All pointers in the wildcard structure are set to NULL after freeing
 * the memory to avoid dangling pointers.
*/
void	*destroy_wildcard(t_wildcard *wildcard)
{
	free(wildcard->pattern);
	free(wildcard->prefix);
	free(wildcard->suffix);
	free(wildcard->base_path);
	destroy_tree(wildcard->tree);
	wildcard->pattern = NULL;
	wildcard->prefix = NULL;
	wildcard->suffix = NULL;
	wildcard->base_path = NULL;
	wildcard->tree = NULL;
	return (NULL);
}