/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:01:05 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 21:58:12 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>

/**
 * 
 * @brief Parses the status of a child process and returns the exit code.
 * 
 * @param status A status code returned by `waitpid` or similar functions.
 * 
 * @note This function checks if the child process exited normally, was
 * terminated by a signal, or was stopped. It returns the appropriate exit
 * code based on the termination scenario.
 * 
 * @return The exit code of the child process.
 * 
 */
int parse_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	return (1);
}

/**
 * @brief Wait for all child processes to finish and return their exit codes.
 * 
 * 
 * @param last_pid The PID of the last child process to wait for.
 * 
 * @note This function will block until all child processes have terminated.
 * It get the status of each child process using `waitpid`.
 * It will handle different termination scenarios, including normal exit,
 * termination by signal, and stopped processes. The exit code of the last
 * terminated child process is returned.
 * 
 * @return The exit code of the last child process that terminated.
 * 
*/
int	wait_childrens(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	exit_code = 0;
    pid = waitpid(-1, &status, 0);
    while (pid > 0)
    {
        if (pid == last_pid)
			exit_code = parse_status(status);
        pid = waitpid(-1, &status, 0);
    }
	return (exit_code);
}
