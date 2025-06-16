/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:44:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/16 17:25:39 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

t_bool	redir_in(t_shell *shell, t_ast *node)
{
	t_dynarray	args;	
	int			fd;
	t_bool		ret;

	args = init_dynarray(3, free_value);
	if (!filter_base_redir(shell, node, &args))
		return (FALSE);
	fd = open(args.data[0], O_RDONLY);
	if (!p_int(fd, -1, args.data[0]))
	{
		destroy_dynarray(&args);
		return (FALSE);
	}
	ret = p_int(dup2(fd, STDIN_FILENO), -1, "dup2");
	close(fd);
	destroy_dynarray(&args);
	return (ret);
}
