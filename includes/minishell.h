/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:48:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/28 19:13:46 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env.h"
# include "shell.h"
# include "token.h"
# include "dynarray.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

t_bool	is_builtin(char **args, t_shell *shell);

t_env	*init_env(char **envp);
void	init_signals(void);

void	expand_env(t_dynarray *arr, t_shell *shell);
void	expand_wildcard(t_dynarray *arr, t_shell *shell);
void	*expand_env_token(t_shell *shell, void *data);
void	*expand_wildcard_token(t_shell *shell, void *data);


void	loop_dynarray(t_dynarray *arr, t_shell *shell, void *(*f)(t_shell *, void *));


#endif