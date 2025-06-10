/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:25:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 01:38:39 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "libft_tree.h"
#include "config.h"

static void	*free_value(void *data)
{
	free(data);
	return (NULL);
}

static void	*free_params(char *key, char *value)
{
	free(key);
	free(value);
	return (NULL);
}

/**
 * @brief Initializes a wildcard tree node.
 *
 * @param key The key of the node.
 * @param value The value of the node.
 * 
 * @note The key and value must be allocated strings.
 * If one of them is NULL, the function will free both
 * and return NULL.
 * 
 * @return The initialized tree node or NULL if an error occurred.
 */
t_tree	*init_wildcard_tree(char *key, char *value)
{
	const char	charset[] = {-SYMBOL_GLOB_ANY, -SYMBOL_GLOB_ONE, '\0'};
	t_tree		*node;

	if (!key || !value)
		return (free_params(key, value));
	ft_strpositivate(&key, charset);
	ft_strpositivate(&value, charset);
	node = init_tree_node(key, value, &ft_strcasecmp, &free_value);
	if (!node)
		return (free_params(key, value));
	return (node);
}
