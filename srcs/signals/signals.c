#include "minishell_signal.h"
#include <readline/readline.h>

# define _XOPEN_SOURCE 700
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>

volatile sig_atomic_t g_sig = 0;

void	sigint_handler_heredoc(int sig)
{
	g_sig = sig;
	//ft_putendl_fd("", 1);
	//rl_replace_line("huhu", 0);
	//rl_on_new_line();
	//rl_redisplay();
	//rl_catch_signals = 1;
	//rl_done = 1;
	close(0);
}

void	sigint_handler_shell(int sig)
{
	(void) sig;

	write(1, "\n", 1);
	rl_replace_line("", 0); //remet la ligne à 0;
	rl_on_new_line();
	rl_redisplay();
}



void	heredoc_handler(int signo, siginfo_t *info, void *context)
{
	(void) signo;
	(void) info;
	(void) context;
	g_sig = signo;
	ft_putendl_fd("", 2);
	rl_replace_line("", 0);
	close(0);
}

void	prompt_handler(int signo, siginfo_t *info, void *context)
{
	(void) signo;
	(void) info;
	(void) context;
	ft_putendl_fd("", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	exec_handler(int signo, siginfo_t *info, void *context)
{
	(void) signo;
	(void) info;
	(void) context;
	rl_replace_line("", 0);
}



void	signals(t_signal_ctx ctx)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (ctx == SIGCTX_HEREDOC)
		signal(SIGINT, &sigint_handler_heredoc);
	else if (ctx == SIGCTX_SHELL)
		signal(SIGINT, &sigint_handler_shell);
	else if (ctx == SIGCTX_FORK)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
