/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:01:05 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 04:51:54 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>

/**
 * @brief Wait for all child processes to finish and return their exit codes.
 * 
 * This function will block until all child processes have terminated.
 * It will handle different termination scenarios, including normal exit,
 * termination by signal, and stopped processes. The exit code of the last
 * terminated child process is returned.
 * 
*/
int	wait_childrens(int last_pid)
{
	pid_t	pid;
	int		status;
	int		exit_code;

    pid = waitpid(-1, &status, 0);
	exit_code = 0;
    while (pid > 0)
    {
        if (pid == last_pid)
        {
            if (WIFEXITED(status))
                exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                exit_code = 128 + WTERMSIG(status);
            else
                exit_code = 1;
        }
        pid = waitpid(-1, &status, 0);
    }
	return (exit_code);
}