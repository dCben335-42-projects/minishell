/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:36:28 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/09 17:03:59 by bcabocel         ###   ########.fr       */
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
void	fork_and_exec(t_shell *shell, char **argv, t_dynarray *cmd);

void		*destroy_child(t_shell *shell, char **argv, int exit_code);
t_dynarray	*cmd_to_argv(t_dynarray *arr, t_dynarray *argv);

t_bool	is_cmd_redirection(t_dynarray *cmd);
t_bool	handle_redirections(t_shell *shell, t_dynarray *cmd);
void	restore_std_in_out(int saved_stdin, int saved_stdout);
void	close_fds(void);
void f_savestd(
	t_shell *shell,
	t_dynarray *cmd,
	char **args,
	void (*f)(t_shell *, char **)
);

#endif