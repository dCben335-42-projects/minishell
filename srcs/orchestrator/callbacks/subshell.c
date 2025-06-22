/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:04:49 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/22 15:36:12 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orchestrator.h"
#include "cmd.h"
#include "utils.h"
#include <signal.h>
#include <sys/types.h>
#include "signals.h"

static t_ast	*run_subshell_redir(
	t_shell *shell,
	t_ast *cmd,
	t_ast *skipped_cmd
)
{
	const int	saved_stdin = dup(STDIN_FILENO);
	const int	saved_stdout = dup(STDOUT_FILENO);
	t_ast		*ret;

	if (!p_int(saved_stdin, -1, "dup")
		|| !p_int(saved_stdout, -1, "dup")
		|| !redirect(shell, skipped_cmd->content))
	{
		restore_std_in_out(saved_stdin, saved_stdout);
		shell->exit_code = EXIT_FAILURE;
		return (NULL);
	}
	ret = exec_subshell(shell, cmd);
	restore_std_in_out(saved_stdin, saved_stdout);
	return (find_next_cmd(ret));
}

/**
 * @brief Executes the subshell command with redirection in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute
 * 	or NULL if there are no more commands.
 */
t_ast	*exec_subshell_redir(t_shell *shell, t_ast *cmd)
{
	t_ast	*subshell_cmd;
	t_ast	*redir_cmd;

	subshell_cmd = find_next_cmd(cmd);
	redir_cmd = skip_cmd(subshell_cmd);
	return (run_subshell_redir(shell, subshell_cmd, redir_cmd));
}

/**
 * 
 * @brief Executes the subshell command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute
 * 	or NULL if there are no more commands.
 * 
 */
t_ast	*exec_subshell(t_shell *shell, t_ast *cmd)
{
	t_ast	*skipped_cmd;

	skipped_cmd = skip_cmd(cmd);
	shell->last_pid = fork();
	if (!p_int(shell->last_pid, -1, "fork"))
	{
		shell->exit_code = EXIT_FAILURE;
		return (NULL);
	}
	signals(SIGCTX_CAPT);
	if (shell->last_pid == 0)
	{
		cmd = find_next_cmd(cmd);
		while (!g_sig && cmd && cmd != skipped_cmd)
			cmd = call_cmd(shell, cmd);
		destroy_self(shell, NULL, shell->exit_code);
	}
	shell->exit_code = wait_childrens(shell->last_pid);
	signals(SIGCTX_SHELL);
	return (skipped_cmd);
}
