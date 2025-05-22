/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:01:53 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 18:11:47 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"
#include "struct_lexer_args.h"

static int	create_fd(char *content)
{
	int		fd[2];

	if (!content)
		return (-1);
	if (!p_int(pipe(fd), -1, "pipe"))
		return (-1);
	if (!p_int(write(fd[1], content, ft_strlen(content)), -1, "write")
		|| !p_int(write(fd[1], "\n", 1), -1, "write"))
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	close(fd[1]);
	return (fd[0]);
}

static t_bool is_expandable(t_dynarray *arr)
{
	const t_ast_node	*node = get_dynarray_value(arr, 1);
	
	return (ft_strcmp(node->content, HEREDOC_EXPANDABLE_TRUE) == 0);
}

t_bool	redir_heredoc(t_shell *shell, t_ast_node *node)
{
	const t_ast_node	*value_node = get_dynarray_value(node->content, 0);
	int					fd;
	t_bool				ret;

	if (is_expandable(node->content))
		fd = create_fd(expand_env_str(shell, (char **)&value_node->content));
	else 
		fd = create_fd(value_node->content);
	if (fd == -1)
		return (FALSE);
	ret = p_int(dup2(fd, STDIN_FILENO), -1, "dup2");
	close(fd);
	return (ret);
}
