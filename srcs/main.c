/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:31:21 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 20:08:12 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "minishell.h"
#include "cmd.h"
#include "minishell_signal.h"
#include "utils.h"
#include "libft.h"
#include "math_utils.h"

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


void set_default_env(t_shell *shell)
{
	char	*pwd;

	if (!get_env_node(shell->env, ENV_PATH_KEY))
		add_env_node(&shell->env, init_env_node(ENV_PATH_KEY"=""/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"));
	if (!get_env_node(shell->env, ENV_PWD_KEY) && shell->current_path)
	{
		pwd = ft_strjoin(ENV_PWD_KEY"=", shell->current_path);
		if (pwd)
		{
			add_env_node(&shell->env, init_env_node(pwd));
			free(pwd);
		}
	}
	if (!get_env_node(shell->env, ENV_OLDPWD_KEY))
		add_env_node(&shell->env, init_env_node(ENV_OLDPWD_KEY"="""));
}

t_bool ft_is_only_one_number(const char *str)
{
	t_bool	is_space_between;

	while (ft_isspace(*str))
		str++;
	is_space_between = FALSE;
	while (*str)
	{
		if (ft_isspace(*str))
		{
			is_space_between = TRUE;
			while (ft_isspace(*str))
				str++;
			continue;
		}
		else if (!ft_isdigit(*str) || is_space_between)
			return (FALSE);
		str++;
	}
	return (TRUE);
}

void update_shlvl(t_shell *shell)
{
	t_env	*shlvl_node;
	char	*new_val;
	int		shlvl;

	shlvl_node = get_env_node(shell->env, "SHLVL");
	if (shlvl_node)
	{
		shlvl = 1;
		if (shlvl_node->value && ft_is_only_one_number(shlvl_node->value))
			shlvl += ft_atoi_base(shlvl_node->value, BASE_10);
		new_val = ft_itoa_base(shlvl, BASE_10);
		if (new_val)
		{
			free(shlvl_node->value);
			shlvl_node->value = new_val;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;

	(void)argc;
	(void)argv;
	if (PRINT_BANNER)
		print_shell_banner();
	shell = init_shell(envp);
	set_default_env(&shell);
	update_shlvl(&shell);
	handle_loop(&shell);
	ft_exit(&shell, NULL);
	return (0);
}
