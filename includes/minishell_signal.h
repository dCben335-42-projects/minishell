#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <string.h>
# include <termios.h>
# include "libft.h"

extern volatile sig_atomic_t g_heredoc_interrupted;

void	get_termios(struct termios *minishell_term);
void	update_termios(struct termios *minishell_term);
void	restore_termios(void);

void	enable_sigquit(void);
void	disable_sigquit(void);
void	enable_sigint(void);
void	disable_sigint(void);
void	signal_handler(int signum);
void	enable_sigint_default(void);
void	enable_sigint_heredoc(void);

#endif