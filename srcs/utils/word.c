/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:37:25 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 07:16:25 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_node.h"
#include "struct_shell.h"

t_bool is_word_wildcard(t_dynarray *word)
{
	t_ast_node	*node;
	t_uint		i;

	i = 0;
	while (i < word->count)
	{
		node = (t_ast_node *)get_dynarray_value(word, i);
		if (node->type == CMD_WILDCARD)
			return (TRUE);
		if (node->type == CMD_EXPAND && ft_strchr(node->content, SYMBOL_GLOB_ANY))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char *word_join(t_dynarray *word)
{
	t_ast_node	*node;
	char	*join;
	char	*tmp;
	t_uint	i;

	join = ft_strdup("");
	if (!join)
		return (NULL);
	i = 0;
	while (i < word->count)
	{
		node = (t_ast_node *)get_dynarray_value(word, i);
		tmp = ft_strjoin(join, (char *)node->content);
		if (!tmp)
		{
			free(join);
			return (NULL);
		}
		free(join);
		join = tmp;
		i++;
	}
	return (join);
}
