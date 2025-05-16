/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:36:28 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/16 20:37:28 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include "struct_shell.h"
#include "cmd_expand.h"
#include "cmd_builtin.h"
#include  <sys/types.h>

int		command_handler(char *input, t_shell *shell);

int		wait_childrens(void);
t_bool	is_valid_cmd_path(char *path, int *exit_code);
char	*get_full_cmd_path(char **cmd, t_env *path);
void	exec_cmd(char **argv, t_shell *shell);
void	fork_and_exec(t_shell *shell, char **argv, t_dynarray *cmd);

void	*destroy_self(t_shell *shell, char **argv, int exit_code);

t_bool	is_redirection(t_node_type type);
t_bool	is_cmd_redirection(t_dynarray *cmd);
t_bool	handle_redirections(t_shell *shell, t_dynarray *cmd);

#endif