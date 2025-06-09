/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:12:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 16:50:46 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "sys/stat.h"
#include "config.h"

static t_bool	ft_is_path(char *str)
{
	if (*str == '/'
		|| !ft_strncmp(str, "./", 2)
		|| !ft_strncmp(str, "../", 3)
		|| !ft_strcmp(str, "..")
		|| !ft_strcmp(str, ".")
	)
		return (TRUE);
	return (FALSE);
}

static char	*find_path(char *cmd_path, char **paths)
{
	char	*new;
	char	*join[2];
	size_t	i;

	if (!cmd_path || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		join[0] = paths[i];
		join[1] = cmd_path;
		new = ft_strsjoin((const char **)join, 2, "/");
		if (new && !access(new, F_OK))
		{
			ft_strsfree(paths);
			free(cmd_path);
			return (new);
		}
		free(new);
		i++;
	}
	ft_strsfree(paths);
	return (cmd_path);
}

static t_bool  is_path_directory(char *path)
{
	// using lstat to check if the path is a directory
	struct stat	statbuf;
	
	if (lstat(path, &statbuf) == -1)
		return (FALSE);
	return (S_ISDIR(statbuf.st_mode));
}

/**
 * @brief Check if the command path is valid.
 * 
 * @param path The command path to check.
 * @param exit_code Pointer to store the exit code in case of error.
 * 
 * @return TRUE if the command path is valid, FALSE otherwise.
 */
t_bool	is_valid_cmd_path(char *path, int *exit_code)
{
	if (access(path, F_OK) == -1
		|| !ft_strcmp(path, "..") || !ft_strcmp(path, "."))
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": "ERR_NOT_FOUND, 2);
		*exit_code = 127;
		return (FALSE);
	}
	if (!p_int(access(path, X_OK), -1, path))
	{
		*exit_code = 126;
		return (FALSE);
	}
	if (is_path_directory(path))
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": "ERR_IS_DERECTORY, 2);
		*exit_code = 126;
		return (FALSE);
	}
   	return (TRUE);
}

/**
 * @brief Get the full command path from the command and the PATH environment variable.
 * 
 * @param cmd_name The command name to find the path for.
 * @param paths The PATH environment variable.
 * 
 * @return The full command path if found, otherwise the original command.
 */
char	*get_full_cmd_path(char *cmd_name, t_env *root)
{	
	const t_env	*path = get_env_node(root, ENV_PATH_KEY);

	if (!path || !path->value)
		return (cmd_name);
	if (!cmd_name || !*cmd_name || ft_is_path(cmd_name))
		return (cmd_name);
	return (find_path(cmd_name, ft_split(path->value, ":")));
}