/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_master.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:11:30 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/02 19:59:11 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	add_cmd_master(t_ast_node **cmd_prev, t_ast_ctx *args)
{
	if (is_cmd(args, CMD_SEMICOL))
		add_child(args->local.cmd_master, cmd_prev, args);
	else if (args->i == args->end)
		add_child(args->local.cmd_master, &args->local.cmd, args);
	else if (is_cmd(args, CMD_PIPE))
		get_pipe_cmd_wrapper(cmd_prev, args->local.cmd_master, args);
	else if (is_cmd(args, CMD_AND | CMD_OR | CMD_PARENTHESIS_OPEN))
		add_op_cmds(cmd_prev, args->local.cmd_master, args);
	else
		*cmd_prev = args->local.cmd;
}

/**
 * 
 * @brief Extracts commands from tokens and adds them to the master node.
 * 
 * @param args Structure with tokens, indices, and the master command node.
 * 
 * @note The master node can be a cmd_seq or cmd_parenthesis.
 * 
 * @note When a new subshell is encountered, the function 
 * calls itself recursively to handle the new context.
 * 
*/
void	add_master_cmds(t_ast_ctx *args)
{
	t_ast_node		*cmd_prev;

	cmd_prev = NULL;
	while (args->i < args->end)
	{
		if (args->has_malloc_error)
			return ;
		args->local.ctx = CTX_MASTER;
		if (!get_cmd(args))
			continue ;
		add_cmd_master(&cmd_prev, args);
	}
	return ;
}
