/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:40:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 19:05:04 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"
#include "messages.h"
#include "utils.h"

static char	*get_pwd(t_shell *shell)
{
	const t_env	*oldpwd = get_env_node(shell->env, PWD_KEY);
	
	if (oldpwd)
		return (ft_strdup(oldpwd->value));
	return (ft_strdup(""));
}

static void	handle_env(t_shell *shell, char *new_oldpwd)
{
	char	*new_path;
	char	*newpwd;

	new_path = getcwd(NULL, 0);
	newpwd = getcwd(NULL, 0);
	if (!new_oldpwd)
		new_oldpwd = get_pwd(shell);
	if (p_ptr(new_path, ERR_GETCWD) && p_ptr(newpwd, ERR_GETCWD))
		p_ptr(new_oldpwd, ERR_CD);
	if (!new_oldpwd || !new_path || !newpwd)
	{
		free(new_oldpwd);
		free(new_path);
		free(newpwd);
		return ;
	}
	if (!add_existing_env(shell->env, OLDPWD_KEY, new_oldpwd))
		free(new_oldpwd);
	if (!add_existing_env(shell->env, PWD_KEY, newpwd))
		free(newpwd);
	free(shell->current_path);
	shell->current_path = new_path;
}

static t_bool	env_path(void *value, char *err_msg, t_bool is_node)
{
	if (is_node && value)
		value = ((t_env *)value)->value;
	if (!s_ptr(value, err_msg))
		return (FALSE);
	if (chdir(value) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(value);
		return (FALSE);
	}
	if (is_node)
		ft_putendl_fd(value, 1);
	return (TRUE);
}

void	ft_cd(t_shell *shell, char **args)
{
	const char	*pwd = getcwd(NULL, 0);
	t_bool		ret;

	if (args[1] && args[2])
	{
		ft_putendl_fd(ERR_CD_ARGS, 2);
		shell->exit_code = 1;
		return ;
	}
	if (!args[1])
		ret = env_path(get_env_node(shell->env, HOME_KEY),\
			ERR_CD_HOME, TRUE);
	else if (ft_strcmp(args[1], "-") == 0)
		ret = env_path(get_env_node(shell->env, OLDPWD_KEY),\
			ERR_CD_OLDPWD, TRUE);
	else
		ret = env_path(args[1], ERR_CD, FALSE);
	shell->exit_code = !ret;
	if (ret)
		handle_env(shell, (char *)pwd);
	else 
		free((char *)pwd);
}
