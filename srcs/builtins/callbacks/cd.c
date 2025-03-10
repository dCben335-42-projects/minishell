/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:40:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/10 18:11:58 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "messages.h"
#include <stdio.h>

static	void	handle_env(t_shell *shell, char *oldpwd)
{
	char		*newpwd;
	t_env		*oldpwd_env;

	newpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		oldpwd_env = find_env(shell->env, PWD_KEY);
		if (oldpwd_env)
			oldpwd = ft_strdup(oldpwd_env->value);
		else
			oldpwd = ft_strdup("");
	}
	if (!oldpwd || !newpwd)
		perror("malloc");
	if (!oldpwd || !newpwd || !ft_strcmp(oldpwd, newpwd))
	{
		free(oldpwd);
		free(newpwd);
		return ;
	}
	if (!replace_env(shell->env, OLDPWD_KEY, (char *)oldpwd))
		free(oldpwd);
	if (!replace_env(shell->env, PWD_KEY, (char *)newpwd))
		free(newpwd);
}

static	void	handle_home_relative(char *path, char *home)
{
	char	*new_path;

	new_path = ft_strjoin(home, path + 1);
	if (!new_path)
	{
		perror("malloc");
		return ;
	}
	if (chdir(new_path) == -1)
		perror("cd");
	free(new_path);
}

static	void	handle_back(t_shell *shell)
{
	const t_env	*oldpwd = find_env(shell->env, OLDPWD_KEY);
	char	*message;
	
	if (!oldpwd)
	{
		ft_putendl_fd(ERROR_CD_OLDPWD, 2);
		return ;
	}
	if (chdir(oldpwd->value) != -1)
		return ;
	message = ft_strjoin("cd: ", oldpwd->value);
	if (message)
	{
		perror(message);
		free(message);
		return ;
	}
	perror("cd");
}

void	ft_cd(t_shell *shell, char **args)
{
	const t_env *home = find_env(shell->env, HOME_KEY);
	const char	*pwd = getcwd(NULL, 0);

	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		if (!home)
		{
			ft_putendl_fd(ERROR_CD_HOME, 2);
			return ;
		}
		if (chdir(home->value) == -1)
			perror("cd");
	}
	else if (!ft_strcmp(args[1], "-"))
		handle_back(shell);
	else if (ft_strncmp(args[1], "~/", 2) == 0)
		handle_home_relative(args[1], home->value);
	else
		if (chdir(args[1]) == -1)
			perror("cd");
	handle_env(shell, (char *)pwd);
}
