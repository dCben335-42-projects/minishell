/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:45:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 19:05:31 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "cmd.h"
#include "orchestrator.h"
#include "utils.h"

static void	close_in_out(int fds[2])
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
}

static int	*setup_redirections(int fds[2])
{
	if (fds[0] != -1)
	{
		if (!p_int(dup2(fds[0], STDIN_FILENO), -1, "dup2"))
			return (NULL);
		close(fds[0]);
	}
	if (fds[1] != -1)
	{
		if (!p_int(dup2(fds[1], STDOUT_FILENO), -1, "dup2"))
			return (NULL);
		close(fds[1]);
	}
	return (fds);
}

static t_bool	exec_pipe(
	t_shell *shell,
	t_ast_node *cmd,
	int pipefd[2],
	int in_out[2]
)
{
	shell->last_pid = fork();
	if (!p_int(shell->last_pid, -1, "fork"))
	{
		shell->exit_code = EXIT_FAILURE;
		close_in_out(pipefd);
		close_in_out(in_out);
		return (FALSE);
	}
	if (shell->last_pid == 0)
	{
		if (!setup_redirections(in_out))
			destroy_self(shell, NULL, EXIT_FAILURE);
		close_in_out(pipefd);
		handle_cmd(shell, cmd);
		destroy_self(shell, NULL, shell->exit_code);
	}
	close_in_out(in_out);
	return (TRUE);
}

static t_bool	is_pipe(t_shell *shell, int pipefd[2], int input_fd)
{
	if (!p_int(pipe(pipefd), -1, "pipe"))
	{
		shell->exit_code = EXIT_FAILURE;
		if (input_fd != -1)
			close(input_fd);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Executes a pipeline of commands in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @var skipped_cmd The command to execute after the pipeline.
 * @var pipefd The file descriptors for the pipe with the
 * read end at pipefd[0] and the write end at pipefd[1].
 * 
 * @return The next command node to execute
 * 	 or NULL if there are no more commands.
 */
t_ast_node	*exec_pipeline(t_shell *shell, t_ast_node *cmd)
{
	t_ast_node	*skipped_cmd;
	int			pipefd[2];
	int			input_fd;

	input_fd = -1;
	skipped_cmd = skip_cmd(cmd);
	cmd = find_next_cmd(cmd);
	while (cmd && cmd != skipped_cmd)
	{
		pipefd[1] = -1;
		if ((cmd->next && !is_pipe(shell, pipefd, input_fd))
			|| !exec_pipe(shell, cmd, pipefd, (int [2]){input_fd, pipefd[1]}))
			return (NULL);
		if (input_fd != -1)
			close(input_fd);
		input_fd = pipefd[0];
		cmd = skip_cmd(cmd);
	}
	if (input_fd != -1)
		close(input_fd);
	shell->exit_code = wait_childrens(shell->last_pid);
	return (skipped_cmd);
}
