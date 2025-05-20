/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:58:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 09:04:25 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orchestrator.h"

/**
 * @brief Executes the OR command in the shell.
 * @note If the exit code of the shell is not 0, it executes the next command.
 * Otherwise, it skips the command.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute
 * 	or NULL if there are no more commands.
 */
t_ast_node	*exec_or(t_shell *shell, t_ast_node *cmd)
{
	if (shell->exit_code)
		return (handle_cmd(shell, find_next_cmd(cmd)));
	return (skip_cmd(cmd));
}
