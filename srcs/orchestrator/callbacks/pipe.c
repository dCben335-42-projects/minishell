#include "minishell.h"
#include "cmd.h"
#include "orchestrator.h"


void	handle_sigpipe(int signum)
{
	if (signum == SIGPIPE)
		exit(141);
}

t_bool exec_pipe_segment(t_shell *shell, t_ast_node *cmd, int input_fd, int output_fd, int *pipefd)
{
    shell->last_pid = fork();

    if (shell->last_pid == -1)
    {
        perror("fork");
        shell->exit_code = EXIT_FAILURE;
        return FALSE;
    }
    else if (shell->last_pid == 0)
    {
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
        if (input_fd != -1)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != -1)
        {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        if (pipefd)
        {
            close(pipefd[0]);
            close(pipefd[1]);
        }
        handle_cmd(shell, cmd);
		destroy_self(shell, NULL, shell->exit_code);
	}
	else
	{
		if (pipefd)
		{
			close(pipefd[1]);
			if (input_fd != -1)
				close(input_fd);
		}
		if (input_fd != -1)
			close(input_fd);
    }
    if (input_fd != -1)
        close(input_fd);
    if (output_fd != -1)
        close(output_fd);
    return TRUE;
}



/**
 * @brief Executes the PIPE command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute or NULL if there are no more commands.
 */
t_ast_node *exec_pipe(t_shell *shell, t_ast_node *cmd)
{
    t_ast_node *end = skip_cmd(cmd);
    int pipefd[2];
    int input_fd = -1;
    int output_fd;
    t_ast_node *current;

    current = find_next_cmd(cmd);
    while (current && current != end)
    {
        if (current->next)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                shell->exit_code = EXIT_FAILURE;
                return NULL;
            }
            output_fd = pipefd[1];
        }
        else
            output_fd = -1;

        exec_pipe_segment(shell, current, input_fd, output_fd, current->next ? pipefd : NULL);
        input_fd = (current->next && current->next != end) ? pipefd[0] : -1;
        current = find_next_cmd(current);
    }
    if (input_fd != -1)
        close(input_fd);

    shell->exit_code = wait_childrens(shell->last_pid);
    return end;
}