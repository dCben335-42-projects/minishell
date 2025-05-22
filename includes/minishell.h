/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:48:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 19:06:20 by bcabocel         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "orchestrator.h"

void	init_signals(void);

#endif