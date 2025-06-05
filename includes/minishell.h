/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:48:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 21:45:01 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PRINT_BANNER 0

# include "ast.h"
# include "struct_shell.h"
# include "struct_token.h"
# include "parsing.h"
# include "cmd_expand.h"
# include "cmd_builtin.h"
# include "config.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "orchestrator.h"

#endif