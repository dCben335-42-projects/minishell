/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:31:21 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 12:59:25 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "minishell.h"
#include "cmd.h"

volatile sig_atomic_t g_signal = 0;

static void	handle_loop(t_shell *shell)
{
	char	*input;
	char	**args;
	(void)args;
	(void)shell;
	
	get_lexer_token_def();
	while (TRUE)
	{
		input = readline(SHELL_NAME);
		if (!input)
			break ;
		if (*input)
			command_handler(input, shell);
		free(input);
		printf("exit code: %d\n", shell->exit_code);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	init_signals();
	handle_loop(&shell);
	ft_exit(&shell, NULL);
	return (0);
}
