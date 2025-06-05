/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:55:57 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/05 21:56:29 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	SIGCTX_JUMP
}	t_signal_ctx;

extern volatile sig_atomic_t	g_sig;

void	signals(t_signal_ctx ctx);

#endif