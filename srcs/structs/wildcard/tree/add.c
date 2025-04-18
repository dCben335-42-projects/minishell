/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:27:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:56:41 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "libft_tree.h"

t_tree	*add_wildcard_tree(t_wildcard *wildcard, t_tree *node)
{
	return (add_tree_node(&wildcard->tree, node));
}
