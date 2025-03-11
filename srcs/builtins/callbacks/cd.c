/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:40:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/11 02:59:54 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "messages.h"
#include <stdio.h>

static char	*get_oldpwd(t_shell *shell)
{
	const t_env	*oldpwd = find_env(shell->env, PWD_KEY);

	if (oldpwd)
		return (ft_strdup(oldpwd->value));
	return (ft_strdup(""));
}

static	void	handle_env(t_shell *shell, char *new_oldpwd)
{
	char		*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!new_oldpwd)
		new_oldpwd = get_oldpwd(shell);
	if (!newpwd)
		perror(ERROR_GETCWD);
	if (!new_oldpwd)
		perror(ERROR_CD);
	if (!new_oldpwd || !newpwd || !ft_strcmp(new_oldpwd, newpwd))
	{
		free(new_oldpwd);
		free(newpwd);
		return ;
	}
	free(shell->current_path);
	shell->current_path = ft_strdup(newpwd);
	if (!replace_env(shell->env, OLDPWD_KEY, new_oldpwd))
		free(new_oldpwd);
	if (!replace_env(shell->env, PWD_KEY, newpwd))
		free(newpwd);
}

static	void	handle_home_relative(char *path, char *home)
{
	char	*new_path;

	new_path = ft_strjoin(home, path + 1);
	if (!new_path)
	{
		perror(ERROR_CD);
		return ;
	}
	if (chdir(new_path) == -1)
		perror(ERROR_CD);
	free(new_path);
}

static	void	handle_back(t_shell *shell)
{
	const t_env	*oldpwd = find_env(shell->env, OLDPWD_KEY);
	char		*message;

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
	const t_env	*home = find_env(shell->env, HOME_KEY);
	const char	*pwd = getcwd(NULL, 0);

	if (!args[1] || *args[1] == '~')
	{
		if (!home)
		{
			ft_putendl_fd(ERROR_CD_HOME, 2);
			return ;
		}
		if (chdir(home->value) == -1)
			perror(ERROR_CD);
	}
	else if (*args[1] == '-')
		handle_back(shell);
	else if (ft_strncmp(args[1], "~/", 2) == 0)
		handle_home_relative(args[1], home->value);
	else
		if (chdir(args[1]) == -1)
			perror(ERROR_CD);
	handle_env(shell, (char *)pwd);
}
