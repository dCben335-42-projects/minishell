/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:55:57 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/10 01:33:50 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "struct_shell.h"
# include <sys/wait.h>
# include <signal.h>

typedef enum e_signal_ctx
{
	SIGCTX_HEREDOC,
	SIGCTX_SHELL,
	SIGCTX_FORK,
	SIGCTX_CAPT
}	t_signal_ctx;

extern volatile sig_atomic_t	g_sig;

void	sig_process(t_shell *shell, t_bool is_cmd);
void	signals(t_signal_ctx ctx);

#endif