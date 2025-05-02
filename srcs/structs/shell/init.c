/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:49:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/02 14:33:45 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "messages.h"
#include <unistd.h>
#include <sys/ioctl.h>

t_shell	init_shell(char **envp)
{
	t_shell	shell;

	shell.exit_code = 0;
	shell.env = init_env(envp);
	shell.current_path = getcwd(NULL, 0);
	shell.ast = NULL;
	if (!shell.current_path)
		perror(ERROR_SHELL_INIT);
	return (shell);
}
