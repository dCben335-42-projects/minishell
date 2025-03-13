/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:48:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/13 19:53:16 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env.h"
# include "shell.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

t_bool	is_builtin(char **args, t_shell *shell);

t_env	*init_env(char **envp);
void	init_signals(void);

#endif