/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:29:31 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 14:05:24 by bcabocel         ###   ########.fr       */
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

t_bool	is_valid_filename(t_tree *tree, char *joined_word)
{
	if (get_size_tree(tree) != 1)
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


