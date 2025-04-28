/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:31:21 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/28 20:55:53 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "minishell.h"
#include "cmd.h"

static void	handle_loop(t_shell *shell)
{
	char	*input;
	char	**args;

	while (TRUE)
	{
		input = readline(SHELL_NAME);
		if (!input)
			break ;
		args = ft_split(input, ' ');
		command_handler(input, shell);
		if (args[0])
			is_builtin(args, shell);
		ft_free_split(args);
		printf("exit code: %d\n", shell->exit_code);
	}
}

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
