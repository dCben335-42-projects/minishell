#include "minishell_signal.h"

void enable_sigquit(void)
{
	//struct termios	minishell_term;

	//get_termios(&minishell_term);
	//minishell_term.c_lflag |= ISIG;
	//minishell_term.c_cc[VQUIT] = 28;
	//update_termios(&minishell_term);
	signal(SIGQUIT, SIG_DFL);
}

void disable_sigquit(void)
{
	//struct termios	minishell_term;

	//get_termios(&minishell_term);
    //minishell_term.c_lflag &= ~ISIG;
    //minishell_term.c_cc[VQUIT] = 0;
	//update_termios(&minishell_term);
	signal(SIGQUIT, &signal_handler);
}
