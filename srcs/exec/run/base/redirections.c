/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:01:55 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/06 17:55:51 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "ast_node.h"
#include <fcntl.h>
#include <unistd.h>
#include "errors.h"

void restore_std_in_out(int saved_stdin, int saved_stdout);

typedef struct s_redir_map
{
	t_node_type	type;
	int			flags;
	int 		mode;
}	t_redir_map;

static const t_redir_map *get_redir_map(void)
{
	static const t_redir_map redir_map[] = {
		{CMD_REDIR_OUT, O_WRONLY | O_CREAT | O_TRUNC, 0644},
		{CMD_APPEND, O_WRONLY | O_CREAT | O_APPEND, 0644},
		{CMD_REDIR_IN, O_RDONLY, 0},
		{CMD_HEREDOC, O_RDONLY | O_CREAT | O_APPEND, 0644},
		{0, 0, 0}
	};

	return (redir_map);
}

static int  open_redirection(t_node_type type, const char *filename)
{
	const t_redir_map	*redir_map = get_redir_map();

	while (redir_map->type)
	{
		if (redir_map->type == type)
			return (open(filename, redir_map->flags, redir_map->mode));
		redir_map++;
	}
	return (-1);
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



t_bool	handle_redirections(t_dynarray *cmd)
{
	t_ast_node	*node;
	t_ast_node	*target;
	int			fd;
	t_uint		i = 0;

	while (i < cmd->count)
	{
		node = (t_ast_node *)cmd->data[i];

		if (is_redirection(node->type))
		{
			t_uint j = i + 1;
			while (j < cmd->count && ((t_ast_node *)cmd->data[j])->type == CMD_SPACE)
				j++;
			if (j >= cmd->count || ((t_ast_node *)cmd->data[j])->type != CMD_TEXT)
				return (FALSE);
			target = (t_ast_node *)cmd->data[j];
			fd = open_redirection(node->type, target->content);
			if (!p_int(fd, -1, target->content))
				return (FALSE);
			if (node->type == CMD_REDIR_IN)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		i++;
	}
	return (TRUE);
}
