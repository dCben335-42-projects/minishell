/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:44:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/27 19:11:49 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

t_bool	redir_in(t_shell *shell, t_ast_node *node)
{
	t_dynarray	*args;	
	int			fd;
	t_bool		ret;

	args = filter_base_redir(shell, node);
	if (!args)
		return (FALSE);
	fd = open(args->data[0], O_RDONLY);
	if (!p_int(fd, -1, args->data[0]))
		return ((t_bool) destroy_dynarray(args));
	ret = p_int(dup2(fd, STDIN_FILENO), -1, "dup2");
	close(fd);
	destroy_dynarray(args);
	return (ret);
}
