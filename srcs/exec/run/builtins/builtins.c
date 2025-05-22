/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:14:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 21:29:26 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "errors.h"
#include "utils.h"

static const t_builtin	*get_builtin_map(void)
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
