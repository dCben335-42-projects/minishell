/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:35:51 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/16 16:51:03 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_builder.h"

static void	handle_parenthesis(
	t_ast **cmd_prev,
	t_ast *cmd_master,
	t_ast_ctx *args
)
{
	add_child(cmd_master, cmd_prev, args);
	add_parenthesis_cmd(args, cmd_master);
}

static void	add_cmds(
	t_ast **cmd_prev,
	t_ast *cmd_master,
	t_ast_ctx *args
)
{
	while (!args->has_malloc_error && args->i < args->end)
	{
		args->local.ctx = CTX_OP;
		if (!get_cmd(args))
			continue ;
		if (is_cmd(args, CMD_SEMICOL))
			return (add_child(cmd_master, cmd_prev, args));
		if (args->i == args->end)
			return (add_child(cmd_master, &args->local.cmd, args));
		if (is_cmd(args, CMD_PIPE))
			add_pipe_cmds(cmd_prev, cmd_master, args);
		else if (is_cmd(args, CMD_PARENTHESIS_OPEN))
			handle_parenthesis(cmd_prev, cmd_master, args);
		else if (is_cmd(args, CMD_AND | CMD_OR))
			return (add_child(cmd_master, cmd_prev, args));
		else
			*cmd_prev = args->local.cmd;
	}
}

static void add_in_parenthesis(t_ast *cmd_master, t_ast_ctx *args)
{
	t_ast	*cmd;

	add_parenthesis_cmd_master(cmd_master, args);
	if (args->has_malloc_error)
		return ;
	if (((t_token *)
			get_dynarray_value(args->tokens, args->i))->type == M_SPACE)
		args->i++;
	if (((t_token *)
			get_dynarray_value(args->tokens, args->i))->type == OP_SEMICOL)
	{
		cmd = ast_init_node(args, CMD_SEMICOL);
		if (args->has_malloc_error)
			return ;
		add_child(cmd_master, &cmd, args);
		args->i++;
	}
}

/**
 * 
 * @brief Handles the case where the command is AND/OR/PARENTHESIS operation.
 * 
 * @param cmd_prev Pointer to the previous command node (not yet added).
 * It is either a CMD_BASE node. Other this argument will be NULL.
 * @param cmd_master The master command node to which the new command
 * will be added.
 * @param args The arguments structure containing the tokens and indices.
 * 
 * @note This function also add the previous command node
 * to the master command node if it is not NULL.
 * 
*/
void	add_op_cmds(
	t_ast **cmd_prev,
	t_ast *cmd_master,
	t_ast_ctx *args
)
{
	t_ast	*cmd;

	cmd = args->local.cmd;
	args->local.cmd = &args->local.lcmd;
	add_child(cmd_master, cmd_prev, args);
	if (is_ast_types(cmd, CMD_PARENTHESIS_OPEN))
	{
		add_in_parenthesis(cmd_master, args);
		return ;
	}
	add_cmds(cmd_prev, cmd, args);
	add_child(cmd_master, &cmd, args);
}
