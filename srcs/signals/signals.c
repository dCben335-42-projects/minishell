/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:13:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/06 02:17:39 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_sig = 0;

static void	sigint_handler_heredoc(int sig)
{
	g_sig = sig;
	write(1, "^C", 2);
	close(0);
}

static void	sigint_handler_shell(int sig)
{
	(void) sig;
	write(1, "^C", 2);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sig_capter(int sig)
{
	g_sig = sig;
}

/**
 * 
 * @brief Sets the signal handlers based on the context.
 *
 * @param ctx The context in which the signals are set.
 * 
 */
void	signals(t_signal_ctx ctx)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (ctx == SIGCTX_HEREDOC)
		signal(SIGINT, &sigint_handler_heredoc);
	else if (ctx == SIGCTX_SHELL)
		signal(SIGINT, &sigint_handler_shell);
	else if (ctx == SIGCTX_CAPT)
	{
		signal(SIGINT, &sig_capter);
		signal(SIGQUIT, &sig_capter);
	}
	else if (ctx == SIGCTX_FORK)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
