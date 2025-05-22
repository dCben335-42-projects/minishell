#include "minishell_signal.h"

void enable_sigint(void)
{
	struct termios	minishell_term;

	get_termios(&minishell_term);
	minishell_term.c_lflag |= ISIG;
	minishell_term.c_cc[VINTR] = 3;
	update_termios(&minishell_term);
	signal(SIGINT, SIG_DFL);
}

void enable_sigint_default(void)
{
	struct termios	minishell_term;

	get_termios(&minishell_term);
	minishell_term.c_lflag |= ISIG;
	minishell_term.c_cc[VINTR] = 3;
	update_termios(&minishell_term);
	signal(SIGINT, &signal_handler);
}

void disable_sigint(void)
{
	struct termios	minishell_term;

	get_termios(&minishell_term);
	minishell_term.c_lflag |= ISIG;
	minishell_term.c_cc[VINTR] = 0;
	update_termios(&minishell_term);
	signal(SIGINT, SIG_IGN);
}