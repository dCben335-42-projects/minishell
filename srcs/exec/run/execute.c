/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:07:25 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 15:29:29 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "utils.h"
#include "minishell_signal.h"

/**
 * 
 * @brief Execute a command using execve.
 * 
 * @param shell The shell instance.
 * @param argv The command and its arguments. 
 * It must be a null-terminated array, 
 * Otherwise it will cause undefined behavior.
 * 
 * @note This function is intended to be called in a child process
 * after a fork. It will replace the current process image
 * with the new command.
 * 
 * @note If execve fails, it will print an error message
 * and free the allocated memory for the arguments. It will
 * also destroy the shell instance and exit the process.
 * It is important to ensure that everything is properly cleaned up
 * otherwise it may lead to memory leaks or other issues.
 * 
 * 
*/
static void	exec_cmd(t_shell *shell, char **argv, size_t name_i)
{

	execve(argv[name_i], &argv[name_i], (char **)shell->env_array.data);
	write(STDERR_FILENO, "execve: ", 9);
	perror(argv[0]);
	destroy_self(shell, argv, EXIT_FAILURE);
}



static void	child_exec(t_shell *shell, t_dynarray *cmd, char **argv, size_t name_i) 
{
    int	exit_code;

	exit_code = EXIT_FAILURE;
	if (!redirect(shell, cmd)
		|| !is_valid_cmd_path(argv[name_i], &exit_code))
		destroy_self(shell, argv, exit_code);
	exec_cmd(shell, argv, name_i);
}

/**
 * @brief Fork a new process and execute a command.
 * 
 * @param shell The shell instance.
 * @param cmd  The ast node containing the command to execute.
 * @param argv The command and its arguments with the first argument
 * @param name_i The index of the command name in the argv array.
 * 
 * @note name_i is always 0 if the first argument is not a bang (!).
 * Otherwise, it is 1.
 * 
 * @note This function will fork a new process and execute the command
 * in the child process. The parent process will wait for the child
 * to finish and return its exit code.
 * 
*/
void	fork_and_exec(t_shell *shell, t_dynarray *cmd, char **argv, size_t name_i) 
{
    pid_t pid;

    pid = fork();
	if (!p_int(pid, -1, "fork"))
	{
		shell->exit_code = EXIT_FAILURE;
		return ;
	}
	signals(SIGCTX_JUMP);
    if (pid == 0)
	{
		signals(SIGCTX_FORK);
		child_exec(shell, cmd, argv, name_i);
	}
	shell->exit_code = wait_childrens(pid);
	if (g_sig == SIGINT)
		shell->interrupted = TRUE;
	signals(SIGCTX_SHELL);
}
