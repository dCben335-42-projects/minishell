/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:31:21 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/07 15:35:28 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "minishell.h"
#include "cmd.h"

volatile sig_atomic_t g_signal = 0;

static void	handle_loop(t_shell *shell)
{
	char	*input;

	while (TRUE)
	{
		input = readline(SHELL_NAME);
		if (!input)
			break ;
		command_handler(input, shell);
		printf("exit code: %d\n", shell->exit_code);
	}
}

char *stringify_envs(t_env *env);

int	main(int argc, char **argv, char **envp)
{
	const char	*exit_args[] = {"exit", NULL};
	t_shell		shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	init_signals();
	handle_loop(&shell);
	ft_exit(&shell, (char **)exit_args);
	return (0);
}
