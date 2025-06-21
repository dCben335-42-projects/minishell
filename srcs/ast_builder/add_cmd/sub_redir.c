/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:44:08 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/21 21:17:36 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_builder.h"

void	handle_sub_redir(
	t_ast_ctx *args,
	t_ast *cmd_master,
	t_ast **cmd
)
{
	t_ast	*cmd_subredir;
	t_ast	*cmd_pipe;

	cmd_subredir = get_adjacent_cmd(args, -1, TRUE);
	cmd_pipe = NULL;
	if (args->has_malloc_error)
		return ((void)destroy_ast(*cmd));
	if (cmd_subredir)
	{
		add_child(cmd_subredir, cmd, args);
		get_cmd(args);
		add_child(cmd_subredir, &args->local.cmd, args);
		*cmd = cmd_subredir;
		cmd_pipe = get_adjacent_cmd(args, -1, FALSE);
	}
	if (args->has_malloc_error)
		return ((void)destroy_ast(cmd_subredir));
	if (cmd_pipe)
	{
		add_child(cmd_pipe, &cmd_subredir, args);
		args->i++;
		add_cmd_pipe(&cmd_subredir, cmd_pipe, args);
		return (add_child(cmd_master, &cmd_pipe, args));
	}
	add_child(cmd_master, cmd, args);
}

void	handle_sub_redir2(
	t_ast_ctx *args,
	t_ast **cmd_p,
	t_ast **cmd_prev,
	t_ast *cmd_master
)
{
	t_ast	*cmd_subredir;
	t_ast	*cmd_pipe;

	cmd_subredir = get_adjacent_cmd(args, -1, TRUE);
	if (args->has_malloc_error)
		return ((void)destroy_ast(*cmd_p));
	if (cmd_subredir)
	{
		add_child(cmd_subredir, cmd_p, args);
		get_cmd(args);
		add_child(cmd_subredir, &args->local.cmd, args);
		cmd_pipe = get_adjacent_cmd(args, -1, FALSE);
		if (args->has_malloc_error)
			return ((void)destroy_ast(cmd_subredir));
		if (cmd_pipe)
		{
			destroy_ast(cmd_pipe);
			*cmd_prev = cmd_subredir;
		}
		else
			add_child(cmd_master, &cmd_subredir, args);
	}
	else
		add_child(cmd_master, cmd_p, args);
}
