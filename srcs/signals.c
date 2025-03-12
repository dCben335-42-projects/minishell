/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:07:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/12 19:18:51 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "shell.h"
# include <readline/readline.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "libft.h"

static void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
		return ;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	init_signals(void)
{
	struct sigaction	sa;

    sa.sa_flags = 0;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);   
    sigaction(SIGQUIT, &sa, NULL);  
}
