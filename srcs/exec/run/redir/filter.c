/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:17:06 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 15:20:26 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

static char	*word_join(t_dynarray *word)
{
	t_ast_node	*node;
	char		*join;
	char		*tmp;
	t_uint		i;

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

t_dynarray  *filter_base_redir(t_shell *shell, t_ast_node *node, t_dynarray *args)
{
	char		*joined_word;
	
	if (!args->data)
		return (destroy_dynarray(args));
	joined_word = word_join(node->content);
	if (!joined_word)
		return (destroy_dynarray(args));
	if (!expand_word(shell, node->content, args))
		return (ft_free((void **)&joined_word));
	if (!is_valid_filename(args, joined_word))
		return (destroy_dynarray(args));
	return (args);
}
