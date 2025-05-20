#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "cmd.h"
#include "minishell.h"
#include "orchestrator.h"
#include "utils.h"
#include "errors.h"

static int	*setup_redirections(int fds[2])
{
    if (fds[0] != -1)
    {
        if (!p_int(dup2(fds[0], STDIN_FILENO), -1, "pipe"))
			return (NULL);
        close(fds[0]);
    }
    if (fds[1] != -1)
    {
		if (!p_int(dup2(fds[1], STDOUT_FILENO), -1, "pipe"))
			return (NULL);
		close(fds[1]);
    }
	return (fds);
}

static void close_pipesfd(int fds[2])
{
	if (!fds)
		return ;
    if (fds[0] != -1)
        close(fds[0]);
    if (fds[1] != -1)
        close(fds[1]);
}

t_bool exec_pipe_segment(t_shell *shell, t_ast_node *cmd, int fds[2], int *pipefd)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        shell->exit_code = EXIT_FAILURE;
		close_pipesfd(pipefd);
		close_pipesfd(fds);
        return (FALSE);
    }
    else if (pid == 0)
    {
        signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_DFL);
		if (!setup_redirections(fds))
			destroy_self(shell, NULL, EXIT_FAILURE);
        close_pipesfd(pipefd);
        handle_cmd(shell, cmd);
        destroy_self(shell, NULL, shell->exit_code);
    }
    if (pipefd)
        close(pipefd[1]);
    if (fds[0] != -1)
        close(fds[0]);
    shell->last_pid = pid;
    return (TRUE);
}

static t_bool is_pipe(t_shell *shell, int pipefd[2], int fds[2])
{
    if (pipe(pipefd) == -1)
	{
		perror("pipe");
		shell->exit_code = EXIT_FAILURE;
		close_pipesfd(pipefd);
		close_pipesfd(fds);
		return (FALSE);
	}
	fds[1] = pipefd[1];
	return (TRUE);
}

/**
 * @brief Executes a pipeline of commands in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @var fds The file descriptors for the input and output of the command.
 *    	[0] = input,
 * 		[1] = output.
 * 
 * @return The next command node to execute or NULL if there are no more commands.
 */
t_ast_node *exec_pipe(t_shell *shell, t_ast_node *cmd)
{
    t_ast_node	*skipped_cmd;
    int			pipefd[2];
    int			fds[2];

	fds[0] = -1;
	fds[1] = -1;
	skipped_cmd = skip_cmd(cmd);
	cmd = find_next_cmd(cmd);
    while (cmd && cmd != skipped_cmd)
    {
        fds[1] = -1;
        if (cmd->next && !is_pipe(shell, pipefd, fds))
			return (NULL);
        if ((cmd->next && !exec_pipe_segment(shell, cmd, fds, pipefd))
		|| (!cmd->next && !exec_pipe_segment(shell, cmd, fds, NULL)))
			return (NULL);
        fds[0] = pipefd[0];
        if (!cmd->next)
            fds[0] = -1;
        cmd = skip_cmd(cmd);
    }
    close_pipesfd(pipefd);
    shell->exit_code = wait_childrens(shell->last_pid);
    return (skipped_cmd);
}
