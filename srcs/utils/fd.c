/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:14:00 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 19:25:25 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "utils.h"

/**
 * @brief Restores the standard input and output file descriptors.
 *
 * @param saved_stdin The saved standard input file descriptor.
 * @param saved_stdout The saved standard output file descriptor.
 * 
 * @note This function restores the standard input and output file descriptors
 * to their original state by duplicating the saved file descriptors back
 * to STDIN_FILENO and STDOUT_FILENO.
 */
void restore_std_in_out(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		p_int(dup2(saved_stdin, STDIN_FILENO), -1, "dup2");
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		p_int(dup2(saved_stdout, STDOUT_FILENO), -1, "dup2");
		close(saved_stdout);	
	}
}

/**
 * @brief Closes all file descriptors starting from the specified index.
 *
 * This function iterates through file descriptors starting from the given
 * index and closes each one until it reaches the maximum limit of 1024.
 *
 * @param start The starting index for closing file descriptors.
 * 
 * @note This function is typically used to close all file descriptors
 * if they are not needed anymore, such as when a process is exiting.
 */
void	close_fds(unsigned int start)
{
	while (start < 1024)
		close(start++);
}
