/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:04:49 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 15:58:43 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orchestrator.h"
#include "cmd.h"
#include "utils.h"
#include <signal.h>
#include <sys/types.h>
#include "minishell_signal.h"

static t_ast	*run_subshell(
	t_shell *shell, t_ast *cmd, t_ast *skipped_cmd
)
{
	shell->last_pid = fork();
	if (!p_int(shell->last_pid, -1, "fork"))
	{
		shell->exit_code = EXIT_FAILURE;
		return (NULL);
	}
	signals(SIGCTX_CAPT);
	if (shell->last_pid == 0)
	{
		signals(-1);
		cmd = find_next_cmd(cmd);
		while (!g_sig && cmd && cmd != skipped_cmd)
			cmd = call_cmd(shell, cmd);
		destroy_self(shell, NULL, shell->exit_code);
	}
	shell->exit_code = wait_childrens(shell->last_pid);
	signals(SIGCTX_SHELL);
	return (skipped_cmd);
}

static t_ast	*subshell_redir(
	t_shell *shell, t_ast *cmd, t_ast *skipped_cmd
)
{
	const int	saved_stdin = dup(STDIN_FILENO);
	const int	saved_stdout = dup(STDOUT_FILENO);
	t_ast	*return_value;

	if (!p_int(saved_stdin, -1, "dup")
		|| !p_int(saved_stdout, -1, "dup")
		|| !redirect(shell, skipped_cmd->content))
	{
		restore_std_in_out(saved_stdin, saved_stdout);
		shell->exit_code = EXIT_FAILURE;
		return (NULL);
	}
	return_value = run_subshell(shell, cmd, skipped_cmd);
	restore_std_in_out(saved_stdin, saved_stdout);
	return (find_next_cmd(return_value));
}

/**
 * @brief Executes the subshell command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute
 * 	or NULL if there are no more commands.
 */
t_ast	*exec_subshell(t_shell *shell, t_ast *cmd)
{
	t_ast	*skipped_cmd;
	t_bool		is_redir;

	skipped_cmd = skip_cmd(cmd);
	is_redir = is_only_redir(skipped_cmd);
	if (!is_redir)
		return (run_subshell(shell, cmd, skipped_cmd));
	return (subshell_redir(shell, cmd, skipped_cmd));
}
