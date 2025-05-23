/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:49:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/23 22:59:05 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "messages.h"
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
	p_ptr(shell.current_path, ERROR_SHELL_INIT);
	return (shell);
}
