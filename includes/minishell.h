/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:48:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:29:32 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct_shell.h"
# include "struct_token.h"
# include "parsing.h"
# include "cmd_expand.h"
# include "cmd_builtin.h"
# include "messages.h"
# include "errors.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

t_bool	is_builtin(char **args, t_shell *shell);
void	init_signals(void);

#endif