/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:30:42 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/06 03:05:53 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orchestrator.h"

/** 
 * @brief Executes the command after a semicolon.
 * 
 * @param shell The shell structure.
 * @param cmd The command to execute
 * 
 * @return The next command to execute.
 * 
 * This function is called when a semicolon is encountered in the command
 * line. It simply finds the next command to execute after the semicolon.
*/
t_ast	*exec_semicolon(t_shell *shell, t_ast *cmd)
{
	(void) shell;
	return (find_next_cmd(cmd));
}
