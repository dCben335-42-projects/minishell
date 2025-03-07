/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:40:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/07 18:05:12 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static t_bool	is_absolute_path(const char *path)
{
	if (!ft_strncmp(path, "/", 1) || !ft_strncmp(path, "~/", 2))
		return (TRUE);
	return (FALSE);
}

static	void	handle_absolute(char *path, const char *home)
{
	if (*path == '~')
		path++;
	path = ft_strjoin(home, path);
	if (!path)
	{
		perror("malloc");
		return ;
	}
	if (chdir(path) == -1)
	{
		free(path);
		perror("cd");
	}
	free(path);
}

static	void	handle_env(t_shell *shell)
{
	const char *pwd = find_env(shell->env, "PWD")->value;
	char		*oldpwd;
	char		*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("cd");
		return ;
	}
	if (newpwd == pwd)
		return ;
	oldpwd = ft_strdup(pwd);
	replace_env(shell->env, "OLDPWD", (char *)oldpwd);
	replace_env(shell->env, "PWD", (char *)newpwd);
}

void	ft_cd(t_shell *shell, char **args)
{
	const t_env *home = find_env(shell->env, "HOME")->value;

	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		if (chdir(home) == -1)
			perror("cd");
		return ;
	}
	if (is_absolute_path(args[1]))
		handle_absolute(args[1], home);
	else
		if (chdir(args[1]) == -1)
			perror("cd");
	handle_env(shell);
}
