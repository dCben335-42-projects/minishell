/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtin.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:10:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 19:52:44 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_BUILTIN_H
# define CMD_BUILTIN_H

# include "struct_shell.h"

t_bool	is_builtin(t_shell *shell, t_dynarray *cmd, char **args);

/**
 * @brief The builtin structure.
 * 
 * @param name The name of the builtin command.
 * @param f The function pointer to the builtin command to be 
 * called when the first argument is the name of the builtin command.
 * 
 * @note The function pointer is used to call the builtin command.
 */
typedef struct s_builtin
{
	char	*name;
	void	(*f)(t_shell *shell, char **args);
}	t_builtin;

# define BUILTIN_ENV "env"
# define BUILTIN_CD "cd"
# define BUILTIN_EXPORT "export"
# define BUILTIN_UNSET "unset"
# define BUILTIN_PWD "pwd"
# define BUILTIN_EXIT "exit"
# define BUILTIN_ECHO "echo"

void	ft_env(t_shell *shell, char **args);
void	ft_export(t_shell *shell, char **args);
void	ft_unset(t_shell *shell, char **args);
void	ft_pwd(t_shell *shell, char **args);
void	ft_cd(t_shell *shell, char **args);
void	ft_exit(t_shell *shell, char **args);
void	ft_echo(t_shell *shell, char **args);

#endif