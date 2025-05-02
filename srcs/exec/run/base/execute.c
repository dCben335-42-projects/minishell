/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:07:25 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/02 14:45:05 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

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
void	exec_cmd(char **argv, t_shell *shell)
{
	execve(argv[0], argv, NULL);
	perror("execve");
	ft_free_split(argv);
	destroy_shell(shell);
	exit(EXIT_FAILURE);
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
void	fork_and_exec(t_shell *shell, t_dynarray *args, char **argv)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == 0)
	{
		if (!is_valid_cmd_path(argv[0], &exit_code))
		{
			destroy_dynarray(args);
			destroy_shell(shell);
			exit(exit_code);
		}
		exec_cmd(argv, shell);
	}
	shell->exit_code = wait_childrens();
}