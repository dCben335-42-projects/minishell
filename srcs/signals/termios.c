#include "minishell_signal.h"

void	get_termios(struct termios *minishell_term)
{
	if (tcgetattr(STDIN_FILENO, minishell_term) == -1) {
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
}

void	update_termios(struct termios *minishell_term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, minishell_term) == -1) {
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	restore_termios(void)
{
	static t_bool is_init = FALSE;
	static struct termios original_term;


	if (!is_init)
	{
		get_termios(&original_term);
		is_init = TRUE;
	}
	else
	{
		update_termios(&original_term);
		is_init = FALSE;
	}
}