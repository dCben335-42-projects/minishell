/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:58:34 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 09:04:20 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orchestrator.h"

/**
 * @brief Executes the AND command in the shell.
 * @note If the exit code of the shell is 0, it executes the next command.
 * Otherwise, it skips the command.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute
 * 	or NULL if there are no more commands.
*/
t_ast_node	*exec_and(t_shell *shell, t_ast_node *cmd)
{
	if (!shell->exit_code)
		return (handle_cmd(shell, find_next_cmd(cmd)));
	return (skip_cmd(cmd));
}
