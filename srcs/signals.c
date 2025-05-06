/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:07:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/06 19:59:06 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include "libft.h"

extern volatile sig_atomic_t g_signal;

static void	disable_ctrl_backslash(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag &= ~(ISIG);
	term.c_cc[VQUIT] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		return ;
	}
}

void	signal_handler(int signum)
{
	g_signal = signum;
	if (signum == SIGQUIT)
		return ;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_clear_history();
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
	disable_ctrl_backslash();
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
