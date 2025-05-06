/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:56:48 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/06 16:12:03 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "errors.h"

static void	close_and_restore(int fd, int saved_fd)
{
	if (fd != -1)
	{
		p_int(dup2(saved_fd, fd), -1, "dup2");
		close(saved_fd);
	}
}

void restore_std_in_out(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
		close_and_restore(STDIN_FILENO, saved_stdin);
	if (saved_stdout != -1)
		close_and_restore(STDOUT_FILENO, saved_stdout);
}

void	close_fds(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}
