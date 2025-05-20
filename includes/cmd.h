/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:36:28 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 11:38:43 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include "struct_shell.h"
#include "cmd_expand.h"
#include "cmd_builtin.h"
#include "cmd_redir.h"

#include  <sys/types.h>


int		command_handler(char *input, t_shell *shell);

int		wait_childrens(int last_pid);
t_bool	is_valid_cmd_path(char *path, int *exit_code);
char	*get_full_cmd_path(char **cmd, t_env *path);
void	fork_and_exec(t_shell *shell, char **argv, t_dynarray *cmd);

#endif