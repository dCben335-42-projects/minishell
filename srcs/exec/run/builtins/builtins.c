/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:14:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 02:12:15 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "cmd_redir.h"
#include "utils.h"

static const t_builtin	*get_builtin_map(void)
{
	static const t_builtin	map[] = {
	{BUILTIN_ENV, &ft_env},
	{BUILTIN_CD, &ft_cd},
	{BUILTIN_EXPORT, &ft_export},
	{BUILTIN_UNSET, &ft_unset},
	{BUILTIN_PWD, &ft_pwd},
	{BUILTIN_EXIT, &ft_exit},
	{BUILTIN_ECHO, &ft_echo},
	{BUILTIN_DEBUG, &ft_debug},
	{NULL, NULL}};
	
	return (map);
}

static t_bool run_builtin_redir(
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
		|| !redirect(shell, cmd))
	{
		restore_std_in_out(saved_stdin, saved_stdout);
		shell->exit_code = 1;
		return (TRUE);
	}
	if (f)
		f(shell, args);
	else
		shell->exit_code = 0;
	restore_std_in_out(saved_stdin, saved_stdout);
	return (TRUE);
}

t_bool	is_builtin(t_shell *shell, t_dynarray *cmd, char **args)
{
	const t_builtin	*builtin_map = get_builtin_map();

	if (!*args)
		return (run_builtin_redir(shell, cmd, args, NULL));
	while (builtin_map->name)
	{
		if (!ft_strcmp(builtin_map->name, *args))
			return (run_builtin_redir(shell, cmd, args, builtin_map->f));
		builtin_map++;
	}
	return (FALSE);
}
