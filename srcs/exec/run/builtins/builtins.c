/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:14:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/11 02:01:49 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "cmd_redir.h"
#include "utils.h"
#include "config.h"

static const t_builtin	*get_builtin_map(void)
{
	static const t_builtin	map[] = {
	{BUILTIN_ENV, &ft_env, FLAG_BUILTIN_ENV},
	{BUILTIN_CD, &ft_cd, FLAG_BUILTIN_CD},
	{BUILTIN_EXPORT, &ft_export, FLAG_BUILTIN_EXPORT},
	{BUILTIN_UNSET, &ft_unset, FLAG_BUILTIN_UNSET},
	{BUILTIN_PWD, &ft_pwd, FLAG_BUILTIN_PWD},
	{BUILTIN_EXIT, &ft_exit, FLAG_BUILTIN_EXIT},
	{BUILTIN_ECHO, &ft_echo, FLAG_BUILTIN_ECHO},
	{BUILTIN_DEBUG, &ft_debug, FLAG_BUILTIN_DEBUG},
	{BUILTIN_VOID, &ft_void, FLAG_BUILTIN_VOID},
	{NULL, NULL, FALSE}};

	return (map);
}

static t_bool	run_builtin_redir(
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

/**
 * @brief Checks if the command is a builtin command.
 *
 * @param shell The shell structure.
 * @param cmd The command to check.
 * @param args The arguments of the command.
 * 
 * @note If the command is a builtin, it will also execute the builtin
 * function with the provided arguments.
 * 
 * @note If there in no arguments, it will run all redirections
 *
 * @return TRUE if the command is a builtin or empty, FALSE otherwise.
 */
t_bool	is_builtin(t_shell *shell, t_dynarray *cmd, char **args)
{
	const t_builtin	*map = get_builtin_map();

	if (!*args)
		return (run_builtin_redir(shell, cmd, args, NULL));
	while (map->name)
	{
		if (!ft_strcmp(map->name, *args) && map->is_enabled)
			return (run_builtin_redir(shell, cmd, args, map->f));
		map++;
	}
	return (FALSE);
}
