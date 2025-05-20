/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:01:53 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 12:34:12 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

int	create_fd(char *content)
{
	int		fd[2];

	if (!content)
		return (-1);
	if (!p_int(pipe(fd), -1, "pipe"))
		return (-1);
	if (!p_int(write(fd[1], content, ft_strlen(content)), -1, "write"))
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	close(fd[1]);
	return (fd[0]);
}

const t_bool is_expandable(t_dynarray *arr)
{
	const t_ast_node	*first = get_dynarray_value(arr, 0);
	
	return (ft_strcmp(first->content, "<<") == 0);
}


t_bool	redir_heredoc(t_shell *shell, t_ast_node *node)
{
	const t_dynarray	*content = node->content;
	const t_bool 		need_expand = is_expandable(content);
	const t_ast_node	*value_node = get_dynarray_value(content, 1);
	int					fd;
	t_bool				ret;

	if (need_expand)
		fd = create_fd(expand_env_str(shell, (char **)&value_node->content));
	else 
		fd = create_fd(value_node->content);
	if (fd == -1)
		return (FALSE);
	ret = p_int(dup2(fd, STDIN_FILENO), -1, "dup2");
	close(fd);
	return (ret);
}
