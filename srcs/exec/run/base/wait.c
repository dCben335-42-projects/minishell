/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:01:05 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/07 15:34:48 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/types.h>

void	signal_handler(int signum);


/**
 * @brief Wait for all child processes to finish and return their exit codes.
 * 
 * This function will block until all child processes have terminated.
 * It will handle different termination scenarios, including normal exit,
 * termination by signal, and stopped processes. The exit code of the last
 * terminated child process is returned.
 * 
*/
int	wait_childrens(void)
{
	int		status;
	int		exit_code;

	exit_code = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		else if (WIFSTOPPED(status))
			exit_code = 128 + WSTOPSIG(status);
		else
			exit_code = -1;
	}
	return (exit_code);
}