/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:48:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/29 19:05:48 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"
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
# include "ft_printf.h"

t_bool	is_builtin(char **args, t_shell *shell);
void	init_signals(void);

#endif