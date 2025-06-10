/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:58:35 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/10 01:39:48 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "config.h"
#include "orchestrator.h"
#include "signals.h"

static const t_exec_map	*get_exec_map(void)
{
	static const t_exec_map	map[] = {
	{CMD_BASE, &exec_basic},
	{CMD_AND, &exec_and},
	{CMD_OR, &exec_or},
	{CMD_PIPE, &exec_pipeline},
	{CMD_PARENTHESIS, &exec_subshell},
	{CMD_SEMICOL, &exec_semicolon},
	{0, NULL}};

	return (map);
}

/**
 * @brief Checks if the given node type is a valid execution type.
 * 
 * @param type The node type to check.
 * 
 * @return TRUE if the type is valid, FALSE otherwise.
 */
t_bool	is_valid_exec_type(const t_node_type type)
{
	const t_exec_map	*map = get_exec_map();

	while (map->type)
	{
		if (map->type == type)
			return (TRUE);
		map++;
	}
	return (FALSE);
}

/**
 * @brief Handles the execution of a command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute or NULL if there are
 * no more commands.
 */
t_ast	*call_cmd(t_shell *shell, t_ast *cmd)
{
	const t_exec_map	*exec_map = get_exec_map();

	while (exec_map->type)
	{
		if (exec_map->type == cmd->type)
			return (exec_map->f(shell, cmd));
		exec_map++;
	}
	return (NULL);
}

/**
 * 
 * @brief Orchestrator function that handles the execution of
 * commands in the shell.
 * It finds the next command to execute and calls the appropriate
 * handler function.
 * 	
 * @param shell The shell structure containing the current state.
 * 
 * @note This function is responsible for managing the execution
 * flow of commands in the shell. It iterates through the AST
 * (Abstract Syntax Tree) of commands, executing each command
 * in the appropriate context (e.g., subshell, pipe, etc.).
 * The function continues to find and execute commands until there are
 * no more commands to process.
 * 
*/
void	orchestrator(t_shell *shell)
{
	t_ast	*cmd;

	write(1, COMMAND_COL, sizeof(COMMAND_COL));
	cmd = find_next_cmd(shell->ast);
	while (!g_sig && cmd)
		cmd = call_cmd(shell, cmd);
	sig_process(shell, cmd != NULL);
	write(1, RESET_COL, sizeof(RESET_COL));
}
