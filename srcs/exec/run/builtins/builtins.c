/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:14:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/07 15:34:42 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"

#include "ast_node.h"
#include <stdio.h>

void	restore_std_in_out(int saved_stdin, int saved_stdout);
t_bool	handle_redirections(t_dynarray *cmd);
t_bool	is_redirection(t_node_type type);

static const t_builtin	*get_builtin(void)
{
	static const t_builtin	map[] = {
	{ENV, &ft_env},
	{CD, &ft_cd},
	{EXPORT, &ft_export},
	{UNSET, &ft_unset},
	{PWD, &ft_pwd},
	{EXIT, &ft_exit},
	{ECHO, &ft_echo},
	{NULL, NULL}};
	
	return (map);
}

t_bool	is_cmd_redirection(t_dynarray *cmd)
{
	t_ast_node	*node;
	t_uint		i;

	i = 0;
	while (i < cmd->count)
	{
		node = (t_ast_node *)cmd->data[i];
		if (is_redirection(node->type))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void run_builtin(t_shell *shell, char **args, const t_builtin *builtin, t_dynarray *cmd)
{
	const int	saved_stdin = dup(STDIN_FILENO);
	const int	saved_stdout = dup(STDOUT_FILENO);

	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("dup");
		shell->exit_code = 1;
		return ;
	}
	if (!handle_redirections(cmd))
	{
		restore_std_in_out(saved_stdin, saved_stdout);
		shell->exit_code = 1;
		return ;
	}
	builtin->f(shell, args);
	restore_std_in_out(saved_stdin, saved_stdout);
}


t_bool	is_builtin(char **args, t_shell *shell, t_dynarray *cmd)
{
	const t_builtin	*builtin_map = get_builtin();

	while (builtin_map->name)
	{
		if (ft_strcmp(builtin_map->name, args[0]) == 0)
		{
			if (is_cmd_redirection(cmd))
				run_builtin(shell, args, builtin_map, cmd);
			else
				builtin_map->f(shell, args);
			return (TRUE);
		}
		builtin_map++;
	}
	return (FALSE);
}
