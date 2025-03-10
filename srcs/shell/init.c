/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:49:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/10 19:50:51 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "messages.h"
#include <unistd.h>

t_shell	init_shell(char **envp)
{
	t_shell	shell;

	shell.env = create_envs(envp);
	shell.current_path = getcwd(NULL, 0);
	if (!shell.current_path)
		perror(ERROR_SHELL_INIT);
	return (shell);
}