/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:47:36 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/16 21:56:59 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"

static char	*get_value(char *key, t_wildcard *wildcard)
{
	char *new;
	char *tmp;

	if (!key)
		return (NULL);
	new = ft_strdup(key);
	if (!new)
		return (NULL);
	if (wildcard->is_prefix)
	{
		tmp = ft_strjoin(wildcard->prefix, new);
		free(new);
		if (!tmp)
			return (NULL);
		new = tmp;
	}
	if (wildcard->is_suffix)
	{
		tmp = ft_strjoin(new, wildcard->suffix);
		free(new);
		if (!tmp)
			return (NULL);
		new = tmp;
	}
	return (new);
}

static t_tree	*process_last(
	char *entry_name,
	const char *curr_path,
	const char **segs,
	t_wildcard *wildcard
)
{
	t_tree	*node;
	char	*key;
	char	*value;

	key = join_entry(curr_path, entry_name-, segs);
	value = get_value(key, wildcard);
	if (!key || !value)
		return (NULL);
	node = init_tree_node(key, value, &ft_strcasecmp, &basic_destroyer);
	if (!node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	return (add_tree_node(&wildcard->tree, node));
}