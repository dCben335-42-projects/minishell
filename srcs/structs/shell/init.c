/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:49:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 20:08:12 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "config.h"
#include "utils.h"
#include <unistd.h>

/**
 * @brief Initializes the shell structure with the given environment variables.
 *
 * @param envp The environment variables to initialize the shell with.
 * 
 * @return t_shell The initialized shell structure.
 */
t_shell	init_shell(char **envp)
{
	t_shell	shell;

	shell.exit_code = 0;
	shell.env = init_env(envp);
	shell.env_array = env_to_array(shell.env);
	shell.current_path = getcwd(NULL, 0);
	shell.ast = NULL;
	shell.last_pid = -1;
	shell.debug.all = FALSE;
	shell.debug.tokens = FALSE;
	shell.debug.lexer = FALSE;
	shell.debug.ast = FALSE;
	shell.debug.exitcode = FALSE;
	shell.interrupted = FALSE;
	p_ptr(shell.current_path, ERROR_SHELL_INIT);
	return (shell);
}
