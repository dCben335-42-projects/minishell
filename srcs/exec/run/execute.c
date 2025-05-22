/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:07:25 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 20:46:35 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "utils.h"
#include "minishell_signal.h"

/**
 * @brief Execute a command using execve.
 * 
 * @param argv The command and its arguments with the first argument
 * being the command itself. It must be null-terminated
 * @param shell The shell instance.
 * 
 * @note This function is intended to be called in a child process
 * after a fork. It will replace the current process image
 * with the new command.
 * 
 * @note If execve fails, it will print an error message
 * and free the allocated memory for the arguments. It will
 * also destroy the shell instance and exit the process.
 * 
 */
static void	exec_cmd(char **argv, t_shell *shell)
{
	execve(argv[0], argv, (char **)shell->env_array.data);
	perror("execve");
	destroy_self(shell, argv, EXIT_FAILURE);
}

static void	child_exec(t_shell *shell, char **argv, t_dynarray *cmd) 
{
    int	exit_code;
	
	exit_code = EXIT_FAILURE;
	if (!redirect(shell, cmd)
		|| !is_valid_cmd_path(argv[0], &exit_code))
		destroy_self(shell, argv, exit_code);
	exec_cmd(argv, shell);
}

/**
 * @brief Fork a new process and execute a command.
 * 
 * @param shell The shell instance.
 * @param args The dynamic array of arguments.
 * @param argv The casted dynamic array of arguments. This is
 * the same as args, but casted to a char ** so it can be\
 * passed to execve.
 * 
 * @note This function will fork a new process and execute the command
 * in the child process. The parent process will wait for the child
 * to finish and return its exit code.
 * 
 */
void	fork_and_exec(t_shell *shell, char **argv, t_dynarray *cmd) 
{
    pid_t pid;

    pid = fork();
	if (pid == -1)
	{
		perror("fork");
		shell->exit_code = EXIT_FAILURE;
		return ;
	}
	disable_sigint();
    if (pid == 0)
	{
		enable_sigquit();
		enable_sigint();
		child_exec(shell, argv, cmd);
	}
	shell->exit_code = wait_childrens(pid);
	disable_sigquit();
	enable_sigint_default();
}

