/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:10:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 07:20:02 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "utils.h"

static t_bool	is_word_wildcard(t_dynarray *word)
{
	t_ast_node	*node;
	t_uint		i;

	i = 0;
	while (i < word->count)
	{
		node = (t_ast_node *)get_dynarray_value(word, i);
		if (node->type == CMD_WILDCARD)
			return (TRUE);
		if (node->type == CMD_EXPAND && ft_strchr(node->content, '*'))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/**
 * @brief Expands a word by expanding environment variables and wildcards.
 *
 * @param shell The shell instance.
 * @param word The word to expand.
 * 
 * @return The expanded word or NULL if an error occurred.
 */
t_tree	*expand_word(t_shell *shell, t_dynarray *word)
{
	char *joined_word;

	if (!expand_env_word(shell, word))
		return (NULL);
	joined_word = word_join(word);
	if (!joined_word)
		return (NULL);
	if (is_word_wildcard(word))
		return (expand_wildcard_word(shell, joined_word));
	return (init_wildcard_tree(joined_word, ft_strdup(joined_word)));
}
