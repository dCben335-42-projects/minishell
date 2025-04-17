/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:25:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/17 20:29:35 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "libft_tree.h"

t_tree	*init_wildcard_tree(char *key, char *value)
{
	if (!key || !value)
		return (NULL);
	return (init_tree_node(key, value, &ft_strcasecmp, &basic_destroyer));
}
