/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:10:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/07 17:05:25 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "shell.h"

typedef struct s_builtin {
	char	*name;
	void	(*f)(t_shell *shell, char **args);
}	t_builtin;

# define ENV "env"
# define CD "cd"
# define EXPORT "export"
# define UNSET "unset"
# define PWD "pwd"
# define EXIT "exit"
# define ECHO "echo"

void	ft_env(t_shell *shell, char **args);
void	ft_export(t_shell *shell, char **args);
void	ft_unset(t_shell *shell, char **args);
void	ft_pwd(t_shell *shell, char **args);
void	ft_cd(t_shell *shell, char **args);
void	ft_exit(t_shell *shell, char **args);
void	ft_echo(t_shell *shell, char **args);

#endif