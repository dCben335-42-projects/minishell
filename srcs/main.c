/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:31:21 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 17:35:24 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "minishell.h"
#include "cmd.h"
#include "minishell_signal.h"
#include "utils.h"

static void	handle_loop(t_shell *shell)
{
	const char	*readline_arg;
	char		*input;

	signals(SIGCTX_SHELL);
	rl_catch_signals = 0;
	while (TRUE)
	{
		readline_arg = get_main_readline_arg(shell);
		input = readline(readline_arg);
		free((char *)readline_arg);
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		command_handler(input, shell);
		debug_exitcode(shell);
	}
}

static void	print_shell_banner(void)
{
	const char	*banner = \
		ACCENT_COL"\t\t\t Welcome to\n"
		SECOND_COL"\t   ____  _          _ "
		FIRST_COL"_\n"
		SECOND_COL"\t  / ___|| |__   ___| |"
		FIRST_COL" | ___  ___| |_ ___\n"
		SECOND_COL"\t  \\___ \\| '_ \\ / _ \\ |"
		FIRST_COL" |/ _ \\/ __| __/ __|\n"
		SECOND_COL"\t   ___) | | | |  __/ |"
		FIRST_COL" | (_) \\__ \\ |_\\__ \\\n"
		SECOND_COL"\t  |____/|_| |_|\\___|_|"
		FIRST_COL"_|\\___/|___/\\__|___/\n"
		VARIANT_COL"\n""\t\t\tCrafted by\n\t   "
		FIRST_COL"dCben335 (bcabocel)"
		VARIANT_COL" & "
		SECOND_COL"Azall (abonneau)"
		RESET_COL"\n\n";
	write(1, banner, ft_strlen(banner));
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	(void)argc;
	(void)argv;
	print_shell_banner();
	
	shell = init_shell(envp);
	handle_loop(&shell);
	ft_exit(&shell, NULL);
	return (0);
}
