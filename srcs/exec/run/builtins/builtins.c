/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:14:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/09 17:02:24 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"
#include "errors.h"
#include "ast_node.h"
#include <stdio.h>

void	restore_std_in_out(int saved_stdin, int saved_stdout);
t_bool	handle_redirections(t_shell *shell, t_dynarray *cmd);
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

static t_bool	is_cmd_redirection(t_dynarray *cmd)
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


static void f_savestd(
	t_shell *shell,
	t_dynarray *cmd,
	char **args,
	void (*f)(t_shell *, char **)
)
{
	const int	saved_stdin = dup(STDIN_FILENO);
	const int	saved_stdout = dup(STDOUT_FILENO);

	if (!p_int(saved_stdin, -1, "dup") 
		|| !p_int(saved_stdout, -1, "dup") 
		|| !handle_redirections(shell, cmd))
	{
		restore_std_in_out(saved_stdin, saved_stdout);
		shell->exit_code = 1;
		return ;
	}
	if (f)
		f(shell, args);
	restore_std_in_out(saved_stdin, saved_stdout);
}

void	close_fds(void);
#include "unistd.h"
#include "fcntl.h"

t_bool	is_builtin(
	t_shell *shell,
	t_dynarray *cmd,
	char **args,
	t_bool is_forked
)
{
	const t_builtin	*builtin_map = get_builtin();

	if (!*args)
	{
		if (!is_forked && is_cmd_redirection(cmd))
			f_savestd(shell, cmd, args, NULL);
		return (TRUE);
	}
	while (builtin_map->name)
	{
		if (!ft_strcmp(builtin_map->name, args[0]))
		{
			if (!is_forked && is_cmd_redirection(cmd))
				f_savestd(shell, cmd, args, builtin_map->f);
			else
				builtin_map->f(shell, args);
			return (TRUE);
		}
		builtin_map++;
	}
	return (FALSE);
}
