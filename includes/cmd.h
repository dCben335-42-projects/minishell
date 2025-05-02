/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:36:28 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/07 15:27:26 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include "struct_shell.h"

int		command_handler(char *input, t_shell *shell);
t_bool	execute_cmd(char *path, char **args);


int		wait_childrens(void);
t_bool	is_valid_cmd_path(char *path, int *exit_code);
char	*get_full_cmd_path(char **cmd, t_env *path);
void	exec_cmd(char **argv, t_shell *shell);
// void	fork_and_exec(t_shell *shell, t_dynarray *args, char **argv);
void	fork_and_exec(t_shell *shell, t_dynarray *args, char **argv, t_dynarray *cmd);


t_dynarray	*dynarray_to_argv(t_dynarray *arr);


#endif