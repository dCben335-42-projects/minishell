/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:58:30 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/28 13:28:58 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "orchestrator.h"
#include "cmd.h"
#include "utils.h"

/**
 * @brief Executes a basic command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute
 * 	or NULL if there are no more commands.
 */
t_ast_node	*exec_basic(t_shell *shell, t_ast_node *cmd)
{
	t_dynarray	args;
	char		***argv;

	args = init_dynarray(10, free_value);
	if (!cmd_to_argv(shell, cmd->content, &args))
		return (NULL);
	argv = (char ***)&args.data;
	if (!is_builtin(shell, cmd->content, *argv))
	{
		*argv[0] = get_full_cmd_path(*argv, get_env_node(shell->env, "PATH"));
		if (!*argv[0])
			return (destroy_dynarray(&args));
		fork_and_exec(shell, *argv, cmd->content);
	}
	destroy_dynarray(&args);
	return (find_next_cmd(cmd));
}
