#include "minishell_signal.h"
#include <sys/ioctl.h>
#include <readline/readline.h>

volatile sig_atomic_t g_sig = 0;

void enable_sigint(void)
{
	//struct termios	minishell_term;

	//get_termios(&minishell_term);
	//minishell_term.c_lflag |= ISIG;
	//minishell_term.c_cc[VINTR] = 3;
	//update_termios(&minishell_term);
	signal(SIGINT, SIG_DFL);
}

void enable_sigint_default(void)
{
	//struct termios	minishell_term;

	//get_termios(&minishell_term);
	//minishell_term.c_lflag |= ISIG;
	//minishell_term.c_cc[VINTR] = 3;
	//update_termios(&minishell_term);
	signal(SIGINT, &signal_handler);
}

void heredoc_sigint_handler(int sig) {
    (void)sig;

	g_sig = sig;
	ft_putendl_fd("", 2);
	rl_replace_line("", 0);
	close(0);
}


void exec_parent_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

void enable_sigint_heredoc(void)
{
	//struct termios	minishell_term;
	//get_termios(&minishell_term);
	//minishell_term.c_lflag |= ISIG;
	//minishell_term.c_cc[VINTR] = 3;
	//update_termios(&minishell_term);

	signal(SIGINT, &heredoc_sigint_handler);
}

void disable_sigint(void)
{
	//struct termios	minishell_term;

	//get_termios(&minishell_term);
	//minishell_term.c_lflag |= ISIG;
	//minishell_term.c_cc[VINTR] = 0;
	//update_termios(&minishell_term);
	signal(SIGINT, &exec_parent_handler);
}