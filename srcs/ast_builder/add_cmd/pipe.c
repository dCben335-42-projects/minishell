/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:40:10 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/05 20:56:39 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/**
 * 
 * @brief Handles the case where the command is a pipe operation.
 * Add all the child nodes of the cmd_pipe (cmd).
 * Then adds the cmd_pipe to the cmd_master.
 * 
 * @param cmd_prev Pointer to the previous command node (not yet added).
 * @param cmd_master The master command node to which
 * the new cmd_pipe will be added.
 * @param args The arguments structure containing the tokens and indices.
 * 
 * @note cmd defined in this function is a pointer copy
 * of cmd_pipe which is a malloc node
 * this copy is made so as not to lose the reference.
 * 
 * (A new memory space on the stack is assigned to args->local.cmd)
*/
void	get_pipe_cmd_wrapper(
	t_ast_node **cmd_prev,
	t_ast_node *cmd_master,
	t_ast_ctx *args
)
{
	t_ast_node	*cmd;

	cmd = args->local.cmd;
	args->local.cmd = &args->local.lcmd;
	add_child(cmd, cmd_prev, args);
	get_pipe_cmd(cmd_prev, cmd, args);
	add_child(cmd_master, &cmd, args);
}

/**
 * 
 * @brief Extracts commands from tokens and adds them to the cmd_pipe.
 * 
 * @param cmd_prev Pointer to the previous command node (not yet added).
 * @param cmd_master The master command node to which
 * the new cmd_pipe will be added.
 * @param args The AST global context containing the tokens and indices.
 * 
*/
void	get_pipe_cmd(
	t_ast_node **cmd_prev,
	t_ast_node *cmd_master,
	t_ast_ctx *args
)
{
	while (!args->has_malloc_error && args->i < args->end)
	{
		args->local.ctx = CTX_PIPE;
		if (!get_cmd(args))
			continue ;
		printf("cmd type: %d\n", args->local.cmd->type);
		if (is_cmd(args, CMD_SEMICOL))
			return (add_child(cmd_master, cmd_prev, args));
		if (args->i == args->end)
			return (add_child(cmd_master, &args->local.cmd, args));
		else if (is_cmd(args, CMD_PIPE))
			add_child(cmd_master, cmd_prev, args);
		else if (is_cmd(args, CMD_PARENTHESIS_OPEN))
			get_parenthesis_cmd(args, cmd_master);
		else if (!is_cmd(args, CMD_BASE))
			return (add_child(cmd_master, cmd_prev, args));
		else
			*cmd_prev = args->local.cmd;
	}
}
