/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:29:31 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 02:27:51 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

static const t_redir_map	*get_redir_map(void)
{
	static const t_redir_map	redir_map[] = {
	{CMD_REDIR_OUT, &redir_out},
	{CMD_REDIR_IN, &redir_in},
	{CMD_APPEND, &redir_append},
	{CMD_HEREDOC, &redir_heredoc},
	{CMD_HEREDOC_TRIM, &redir_heredoc},
	{0, NULL}};

	return (redir_map);
}

static t_bool	handle_redir(t_shell *shell, t_ast *node)
{
	const t_redir_map	*redir_map = get_redir_map();

	while (redir_map->type)
	{
		if (redir_map->type == node->type)
			return (redir_map->f(shell, node));
		redir_map++;
	}
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

t_bool	is_only_redir(t_ast *cmd)
{
	t_dynarray	*arr;
	t_uint		i;
	t_ast		*node;

	if (!cmd || cmd->type != CMD_BASE)
		return (FALSE);
	i = 0;
	arr = cmd->content;
	while (i < arr->count)
	{
		node = get_dynarray_value(cmd->content, i);
		if (!is_redirection(node->type))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	redirect(t_shell *shell, t_dynarray *cmd)
{
	t_ast	*node;
	t_uint	i;

	i = 0;
	while (i < cmd->count)
	{
		node = get_dynarray_value(cmd, i);
		if (!handle_redir(shell, node))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
