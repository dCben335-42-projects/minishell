/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 02:13:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 04:00:45 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <readline/readline.h>
#include "config.h"
#include "cmd.h"

volatile sig_atomic_t	g_sig = 0;

static void	sigint_handler_heredoc(int sig)
{
	g_sig = sig;
	ft_putstr_fd("^C", 2);
	close(0);
}

static void	sigint_handler_shell(int sig)
{
	g_sig = sig;
	ft_putendl_fd("^C", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sig_capter(int sig)
{
	g_sig = sig;
}

/**
 * @brief Processes the signal received and updates the shell's exit code.
 *
 * @param shell The shell instance to update.
 * @param is_cmd Indicates if the signal was received during command execution.
 * 
 * @note If the signal is SIGQUIT, it prints a message to stderr.
 * If the shell's `need_reverse_code` it means that the last command's first
 * argument is a bang (`!`), it sets the exit code to 0 if the signal
 * was received in the last command, otherwise it sets the exit code
 * to the parsed status of the signal.
 * 
 */
void	sig_process(t_shell *shell, t_bool is_cmd)
{
	if (!g_sig)
		return ;
	if (g_sig == SIGQUIT)
		ft_putstr_fd(ERR_SIGQUIT, 2);
	if (shell->need_reverse_code && !is_cmd)
		shell->exit_code = 0;
	else
		shell->exit_code = parse_status(g_sig);
	write(1, "\n", 1);
	g_sig = 0;
}

/**
 * 
 * @brief Sets the signal handlers based on the context.
 *
 * @param ctx The context in which the signals are set.
 * 
 * @note The context can be one of the following:
 * 
 * - SIGCTX_HEREDOC: For handling signals in heredoc context.
 * 
 * - SIGCTX_SHELL: For handling signals in the main shell context.
 * 
 * - SIGCTX_CAPT: For handling signals in the command capture context.
 * 
 * - SIGCTX_FORK: For handling signals in the forked process context.
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
