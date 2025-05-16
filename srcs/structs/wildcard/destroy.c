/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:58:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/16 19:21:35 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"

/**
 * @brief Destroys the wildcard structure and frees its allocated memory.
 * 
 * @param wildcard The wildcard structure to destroy.
 * @param tree_destroy A boolean indicating whether to destroy the tree
 * 
 * @return NULL
 * 
 * This function frees all the dynamically allocated memory associated with
 * the wildcard structure, including the pattern, prefix, suffix, base path,
 * and the tree.
 * 
*/
void	*destroy_wildcard(t_wildcard *wildcard, t_bool tree_destroy)
{
	free(wildcard->pattern);
	free(wildcard->prefix);
	free(wildcard->suffix);
	free(wildcard->base_path);
	if (tree_destroy)
		destroy_tree(wildcard->tree);
	return (NULL);
}
