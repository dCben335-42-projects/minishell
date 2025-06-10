/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:49:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 22:21:20 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "utils.h"
#include <unistd.h>

static t_debug	init_debug(void)
{
	t_debug	debug;

	debug.all = FALSE;
	debug.tokens = FALSE;
	debug.lexer = FALSE;
	debug.ast = FALSE;
	debug.exitcode = FALSE;
	return (debug);
}

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
	shell.current_path = getcwd(NULL, 0);
	shell.ast = NULL;
	shell.last_pid = -1;
	shell.need_reverse_code = FALSE;
	shell.debug = init_debug();
	p_ptr(shell.current_path, ERROR_SHELL_INIT);
	return (shell);
}
