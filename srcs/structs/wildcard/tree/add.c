/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:27:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/17 20:29:32 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "libft_tree.h"

t_tree	*add_wildcard_tree(t_wildcard *wildcard, t_tree *node)
{
	if (!node)
		return (NULL);
	return (add_tree_node(&wildcard->tree, node));
}
