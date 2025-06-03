/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_and_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:35:51 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/02 20:35:57 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	handle_parenthesis(
	t_ast_node **cmd_prev,
	t_ast_node *cmd_master,
	t_ast_ctx *args
)
{
	add_child(cmd_master, cmd_prev, args);
	get_parenthesis_cmd(args, cmd_master);
}

static void	add_cmds(
	t_ast_node **cmd_prev,
	t_ast_node *cmd_master,
	t_ast_ctx *args
)
{
	while (args->i < args->end)
	{
		if (args->has_malloc_error)
			return ;
		args->local.ctx = CTX_OP;
		if (!get_cmd(args))
			continue ;
		if (is_cmd(args, CMD_SEMICOL))
			return (add_child(cmd_master, cmd_prev, args));
		if (args->i == args->end)
			return (add_child(cmd_master, &args->local.cmd, args));
		if (is_cmd(args, CMD_PIPE))
			get_pipe_cmd_wrapper(cmd_prev, cmd_master, args);
		else if (is_cmd(args, CMD_PARENTHESIS_OPEN))
			handle_parenthesis(cmd_prev, cmd_master, args);
		else if (is_cmd(args, CMD_AND | CMD_OR))
			return (add_child(cmd_master, cmd_prev, args));
		else
			*cmd_prev = args->local.cmd;
	}
}

/**
 * 
 * @brief Handles the case where the command is AND/OR/PARENTHESIS operation.
 * 
 * @param cmd_prev Pointer to the previous command node (not yet added).
 * (It's the operator node other than pipe)
 * @param cmd_master The master command node to which the new command
 * will be added.
 * @param args The arguments structure containing the tokens and indices.
 * 
*/
void	add_op_cmds(
	t_ast_node **cmd_prev,
	t_ast_node *cmd_master,
	t_ast_ctx *args
)
{
	t_ast_node	*cmd;

	cmd = args->local.cmd;
	args->local.cmd = &args->local.lcmd;
	add_child(cmd_master, cmd_prev, args);
	if (is_node(cmd, CMD_PARENTHESIS_OPEN))
	{
		get_parenthesis_cmd_master(cmd_master, args);
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
		return ;
	}
	add_cmds(cmd_prev, cmd, args);
	add_child(cmd_master, &cmd, args);
}
