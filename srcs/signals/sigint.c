#include "minishell_signal.h"
#include <sys/ioctl.h>
#include <readline/readline.h>

volatile sig_atomic_t g_heredoc_interrupted = 0;

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

void heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	rl_replace_line("", 0);
	rl_done = 1; // Indique à readline de terminer la boucle
    char eot = 4; // Ctrl-D
	write(STDOUT_FILENO, &eot, 1); // Affiche un saut de ligne
    //ioctl(STDIN_FILENO, TIOCSTI, &eot);
	//ioctl(STDIN_FILENO, TIOCSTI, "\n"); // Force readline à terminer
	//write(STDOUT_FILENO, "[handler] SIGINT reçu dans heredoc\n", 35);
}

void enable_sigint_heredoc(void)
{
	struct termios	minishell_term;

	rl_catch_signals = 0;
	get_termios(&minishell_term);
	minishell_term.c_lflag |= ISIG;
	minishell_term.c_cc[VINTR] = 3;
	update_termios(&minishell_term);
	signal(SIGINT, &heredoc_sigint_handler);
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