/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:17:06 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/11 03:14:01 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"
#include "config.h"

static char	*word_join(t_dynarray *word)
{
	t_ast	*node;
	char	*join;
	char	*tmp;
	t_uint	i;

	join = ft_strdup("");
	if (!join)
		return (NULL);
	i = 0;
	while (i < word->count)
	{
		node = (t_ast *)get_dynarray_value(word, i);
		if (node->type & (CMD_QUOTED_TEXT | CMD_QUOTED_ENV))
			tmp = ft_strsjoin((const char *[]){join, "\"",
					(char *)node->content, "\""}, 4, NULL);
		else
			tmp = ft_strjoin(join, (char *)node->content);
		free(join);
		if (!tmp)
			return (NULL);
		join = tmp;
		i++;
	}
	return (join);
}

static t_bool	is_valid_filename(t_dynarray *arr, char *joined_word)
{
	if (!arr || !joined_word)
		return (FALSE);
	if (arr->count != 1 || !arr->data[0])
	{
		ft_putstr_fd(joined_word, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		free(joined_word);
		return (FALSE);
	}
	free(joined_word);
	return (TRUE);
}

/**
 * 
 * @brief Filters the base redirection arguments and checks if they are valid.
 * 
 * @param shell The shell structure containing the current state.
 * @param node The AST node representing the redirection.
 * @param args The dynamic array to store the arguments for the redirection.
 * 
 * @return A dynamic array of filtered arguments or NULL if an error occurs.
 * 
 */
t_dynarray	*filter_base_redir(t_shell *shell, t_ast *node, t_dynarray *args)
{
	char	*joined_word;

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
