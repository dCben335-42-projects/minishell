/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:37:25 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/16 15:41:50 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_node.h"
#include "struct_shell.h"

void *loop_word(t_shell *shell, t_dynarray *word, t_bool (*f)(t_shell *, t_ast_node *))
{
	t_ast_node	*node;
	t_uint		i;

	i = 0;
	while (i < word->count)
	{
		node = (t_ast_node *)get_dynarray_value(word, i);
		if (!f(shell, node))
			return (NULL);
		i++;
	}
	return (word);
}

static t_bool is_wildcard_node(t_shell *shell, t_ast_node *node)
{
	(void)shell;
	if (node->type == CMD_WILDCARD)
		return (TRUE);
	if (node->type == CMD_EXPAND && ft_strchr(node->content, '*'))
		return (TRUE);
	return (FALSE);
}

t_bool is_word_wildcard(t_dynarray *word)
{
	// t_ast_node	*node;
	// t_uint		i;

	// i = 0;
	// while (i < word->count)
	// {
	// 	node = (t_ast_node *)get_dynarray_value(word, i);
	// 	if (node->type == CMD_WILDCARD)
	// 		return (TRUE);
	// 	if (node->type == CMD_EXPAND && ft_strchr(node->content, '*'))
	// 		return (TRUE);
	// 	i++;
	// }
	// return (FALSE);
	return ((t_bool) loop_word(NULL, word, &is_wildcard_node));
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