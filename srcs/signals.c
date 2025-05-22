/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:07:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 20:55:20 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include "libft.h"

//static void	disable_ctrl_backslash(void)
//{
//	struct termios	term;

//	if (tcgetattr(0, &term) == -1)
//	{
//		perror("tcgetattr");
//		return ;
//	}
//	term.c_lflag &= ~(ISIG);
//	term.c_cc[VQUIT] = 0;
//	if (tcsetattr(0, TCSANOW, &term) == -1)
//	{
//		perror("tcsetattr");
//		return ;
//	}
//}

void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		printf("Quit: 3\n");
		return ;
	}
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
}
