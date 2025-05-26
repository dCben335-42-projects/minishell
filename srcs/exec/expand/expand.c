/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:10:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 21:02:18 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "utils.h"
#include "libft_tree.h"

void *destroy_expand(t_expand *node)
{
	if (!node)
		return (NULL);
	if (node->is_tree)
		destroy_tree((t_tree *)node->content);
	else 
		free(node->content);
	free(node);
	return (NULL);
}

t_expand *init_expand(t_bool is_tree, void *content)
{
	t_expand	*expand;

	if (!content)
		return (NULL);
	expand = malloc(sizeof(t_expand));
	if (!expand)
	{
		if (is_tree)
			return (destroy_tree((t_tree *)content));
		free(content);
		return (NULL);
	}
	expand->is_tree = is_tree;
	expand->content = content;
	return (expand);
}

void	*destroy_expand_array(t_dynarray *arr)
{
	t_uint	i;
	t_expand	*node;

	if (!arr || !arr->data)
		return (NULL);
	i = 0;
	while (i < arr->count)
	{
		node = (t_expand *)get_dynarray_value(arr, i);
		destroy_expand(node);
		i++;
	}
	return (destroy_dynarray(arr));
}
t_bool	is_word_env(t_dynarray *word);
/**
 * @brief Expands a word by expanding environment variables and wildcards.
 *
 * @param shell The shell instance.
 * @param word The word to expand.
 * 
 * @return The expanded word or NULL if an error occurred.
 */
t_dynarray	*expand_word(t_shell *shell, t_dynarray *word)
{
	t_dynarray	*expand;
	t_expand	*node;
	
	expand = init_dynarray_malloc(10, NULL);
	if (!is_word_env(word) && !is_word_wildcard(word))
	{
		node = init_expand(FALSE, word_join(word));
		if (!node || (!push(expand, node) && !destroy_expand(node)))
			return (destroy_dynarray(expand));
		return (expand);
	}
	// if (!expand_env_word(shell, word))
	// 	return (destroy_expand_array(expand));
	
	if (is_word_wildcard(word))
	{
		node = init_expand(TRUE, expand_wildcard_word(shell, word_join(word)));
		if (!node || (!push(expand, node) && !destroy_expand(node)))
			return (destroy_expand_array(expand));
	}
		
	// return (init_wildcard_tree(joined_word, ft_strdup(joined_word)));
	return (expand);
}
