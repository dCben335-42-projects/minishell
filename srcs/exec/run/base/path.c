/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:12:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/07 15:28:34 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_bool	ft_is_path(char *str)
{
	if (*str == '/'
		|| !ft_strncmp(str, "./", 2)
		|| !ft_strncmp(str, "../", 3)
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
			ft_free_split(paths);
			free(cmd_path);
			return (new);
		}
		free(new);
		i++;
	}
	ft_free_split(paths);
	return (cmd_path);
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
	if (access(path, F_OK) == -1)
	{
		perror(path);
		*exit_code = 127;
		return (FALSE);
	}
	if (access(path, X_OK) == -1)
	{
		perror(path);
		*exit_code = 126;
		return (FALSE);
	}
   	return (TRUE);
}

/**
 * @brief Get the full command path from the command and the PATH environment variable.
 * 
 * @param cmd The command to execute.
 * @param paths The PATH environment variable.
 * 
 * @return The full command path if found, otherwise the original command.
 */
char	*get_full_cmd_path(char **cmd, t_env *path)
{
	if (ft_is_path(cmd[0]) || !path || !path->value)
		return (cmd[0]);
	return (find_path(cmd[0], ft_split(path->value, ':')));
}