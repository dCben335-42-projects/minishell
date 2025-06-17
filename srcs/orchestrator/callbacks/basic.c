/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:58:30 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/17 13:42:06 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orchestrator.h"
#include "cmd.h"
#include "config.h"

static void	*merror(t_shell *shell)
{
	ft_putendl_fd(ERR_MALLOC, 2);
	shell->exit_code = EXIT_FAILURE;
	return (NULL);
}

static size_t	get_cmd_start_index(char **argv)
{
	if (!FLAG_LOGICAL_NEGATION)
		return (0);
	if (!*argv || ft_strcmp(*argv, "!"))
		return (0);
	return (1);
}

/**
 * @brief Executes a basic command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute
 * 	or NULL if there are no more commands.
 */
t_ast	*exec_basic(t_shell *shell, t_ast *cmd)
{
	t_dynarray	args;
	char		**argv;
	size_t		name_i;

	args = init_dynarray(1, free_value);
	if (!cmd_to_argv(shell, cmd->content, &args))
		return (merror(shell));
	argv = (char **)args.data;
	name_i = get_cmd_start_index(argv);
	shell->need_reverse_code = name_i == 1;
	if (!is_builtin(shell, cmd->content, &argv[name_i]))
	{
		argv[name_i] = get_full_cmd_path(argv[name_i], shell->env);
		if (!argv[name_i] && !merror(shell))
			return (destroy_dynarray(&args));
		fork_and_exec(shell, cmd->content, argv, name_i);
	}
	if (name_i == 1)
		shell->exit_code = !shell->exit_code;
	destroy_dynarray(&args);
	return (find_next_cmd(cmd));
}
