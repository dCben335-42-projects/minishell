/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:36:28 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 21:46:34 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "struct_shell.h"
# include "cmd_expand.h"
# include "cmd_builtin.h"
# include "cmd_redir.h"
# include <sys/types.h>

void	*command_handler(char *input, t_shell *shell);

int		wait_childrens(int last_pid);
t_bool	is_valid_cmd_path(char *path, int *exit_code);
char	*get_full_cmd_path(char *cmd_name, t_env *path);
void	fork_and_exec(
			t_shell *shell,
			t_dynarray *cmd,
			char **argv,
			size_t start_i);

#endif