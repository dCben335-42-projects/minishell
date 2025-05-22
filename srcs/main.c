/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:31:21 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 20:55:39 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "minishell.h"
#include "cmd.h"
#include "minishell_signal.h"

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
		if (!*input)
		{
			free(input);
			continue ;
		}
		command_handler(input, shell);
		printf("exit code: %d\n", shell->exit_code);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	(void)argc;
	(void)argv;
	restore_termios();
	disable_sigquit();
	enable_sigint_default();
	shell = init_shell(envp);
	//init_signals();
	handle_loop(&shell);
	restore_termios();
	ft_exit(&shell, NULL);
	return (0);
}
