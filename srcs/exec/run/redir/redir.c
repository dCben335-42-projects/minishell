/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:29:31 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 20:37:41 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

static const t_redir_map *get_redir_map(void)
{
	static const t_redir_map	redir_map[] = {
		{CMD_REDIR_OUT, &redir_out},
		{CMD_REDIR_IN, &redir_in},
		{CMD_APPEND, &redir_append},
		{CMD_HEREDOC, &redir_heredoc},
		{CMD_HEREDOC_TRIM, &redir_heredoc},
		{0, NULL}
	};

	return (redir_map);
}

static t_bool	handle_redir(t_shell *shell, t_ast_node *node)
{
	const t_redir_map	*redir_map = get_redir_map();

	while (redir_map->type)
	{
		if (redir_map->type == node->type)
			return (redir_map->f(shell, node));			
		redir_map++;
	}
	return (FALSE);
}

char *get_redir_filename(t_dynarray *arr)
{
	t_expand	*node;
	t_tree		*tree;

	node = (t_expand *)get_dynarray_value(arr, 0);
	if (node->is_tree)
	{
		tree = (t_tree *)node->content;
		return (tree->value);
	}
	return (node->content);
}

t_bool	is_valid_filename(t_dynarray *arr, char *joined_word)
{
	t_expand	*node;

	if (!arr || !joined_word)
		return (FALSE);
	node = (t_expand *)get_dynarray_value(arr, 0);
	if (arr->count != 1 || !node || (node->is_tree && get_size_tree(node->content) != 1))
	{
		if (!joined_word)
			return (FALSE);
		ft_putstr_fd(joined_word, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		free(joined_word);
		return (FALSE);
	}
	free(joined_word);
	return (TRUE);
}

t_bool	is_redirection(t_node_type type)
{
	const t_redir_map	*redir_map = get_redir_map();

	while (redir_map->type)
	{
		if (redir_map->type == type)
			return (TRUE);
		redir_map++;
	}
	return (FALSE);
}

t_bool	redirect(t_shell *shell, t_dynarray *cmd)
{
	t_ast_node	*node;
	t_uint		i;

	i = 0;
	while (i < cmd->count)
	{
		node = get_dynarray_value(cmd, i);
		if (node->type != CMD_WORD && !handle_redir(shell, node))
			return (FALSE);
		i++;
	}
	return (TRUE);
}


