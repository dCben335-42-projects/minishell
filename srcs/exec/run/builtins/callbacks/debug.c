/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 02:08:03 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 17:07:23 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"

static const t_debug_map *get_debug_map(t_debug *debug)
{
	static t_debug_map map[5] = {0};
	
	if (!map[0].option)
	{
		map[0] = (t_debug_map){DEBUG_ALL_OPTION, &debug->all};
		map[1] = (t_debug_map){DEBUG_TOKENS_OPTION, &debug->tokens};
		map[2] = (t_debug_map){DEBUG_AST_OPTION, &debug->ast};
		map[3] = (t_debug_map){DEBUG_EXITCODE_OPTION, &debug->exitcode};
		map[4] = (t_debug_map){NULL, NULL};
	}
	return (map);
}

static void print_current_debug(t_shell *shell)
{
	const t_debug_map	*map = get_debug_map(&shell->debug);

	printf("Current debug options:\n");
	while (map->option)
	{
		if (*(map->toggle))
			printf("%-25s enabled\n", (map->option + 2));
		else
			printf("%-25s disabled\n", (map->option + 2));
		map++;
	}
}

static t_bool toggle_debug_mode(t_shell *shell, const char *arg)
{
	const t_debug_map	*map = get_debug_map(&shell->debug);

	while (map->option)
	{
		if (!ft_strcmp(arg, map->option))
		{
			*(map->toggle) = !(*(map->toggle));
			if (*(map->toggle))
				printf("enabled debug mode for %s\n", (map->option + 2));
			else
				printf("disabled debug mode for %s\n", (map->option + 2));
			return (TRUE);
		}
		map++;
	}
	return (FALSE);
}

static t_bool run_args(t_shell *shell, char **args)
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		if (!toggle_debug_mode(shell, args[i]))
		{
			printf("Unrecognized option: %s\n", args[i]);
			write(1, DEBUG_HELP_MSG, ft_strlen(DEBUG_HELP_MSG));
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/**
 * @brief My own debuf command.
 * 
 * @param shell The shell structure.
 * @param args The arguments passed to the command.
 * 
 * @note This function is used to toggle debug modes for the shell.
 */
void	ft_debug(t_shell *shell, char **args)
{
	if (!args[1])
	{
		print_current_debug(shell);
		write(1, DEBUG_HELP_MSG, ft_strlen(DEBUG_HELP_MSG));
		shell->exit_code = 1;
		return ;
	}
	if (!ft_strcmp(args[1], DEBUG_HELP_OPTION))
	{
		write(1, DEBUG_OPTIONS_MSG, ft_strlen(DEBUG_OPTIONS_MSG));
		shell->exit_code = 0;
		return ;
	}
	shell->exit_code = !run_args(shell, args);
}
