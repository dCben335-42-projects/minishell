/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:34:49 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 21:35:18 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

t_bool	redir_out(t_shell *shell, t_ast *node)
{
	t_dynarray	args;	
	int			fd;
	t_bool		ret;

	args = init_dynarray(1, free_value);
	if (!filter_base_redir(shell, node, &args))
		return (FALSE);
	fd = open(args.data[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!p_int(fd, -1, args.data[0]))
	{
		destroy_dynarray(&args);
		return (FALSE);
	}
	ret = p_int(dup2(fd, STDOUT_FILENO), -1, "dup2");
	close(fd);
	destroy_dynarray(&args);
	return (ret);
}

