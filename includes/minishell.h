/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:48:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/17 19:06:01 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env.h"
# include "shell.h"
# include "token.h"
# include "dynarray.h"
# include "expand.h"
# include "builtin.h"
# include "types.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

t_bool	is_builtin(char **args, t_shell *shell);

t_env	*init_env(char **envp);
void	init_signals(void);



#endif