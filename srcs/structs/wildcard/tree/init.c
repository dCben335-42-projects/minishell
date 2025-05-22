/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:25:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 19:09:37 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "libft_tree.h"

static void	*free_value(void *data)
{
	free(data);
	return (NULL);
}

static void *free_params(char *key, char *value)
{
	free(key);
	free(value);
	return (NULL);
}

t_tree	*init_wildcard_tree(char *key, char *value)
{
	t_tree	*node;
	
	if (!key || !value)
		return (free_params(key, value));
	node = init_tree_node(key, value, &ft_strcasecmp, &free_value);
	if (!node)
		return (free_params(key, value));
	return (node);
}
