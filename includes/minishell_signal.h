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

typedef enum e_signal_ctx
{
	SIGCTX_HEREDOC,
	SIGCTX_SHELL,
	SIGCTX_FORK,	
}	t_signal_ctx;

extern volatile sig_atomic_t g_sig;

void	signals(t_signal_ctx ctx);

#endif