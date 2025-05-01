/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:07:25 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/01 16:55:25 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
