/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:36:28 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 17:05:03 by bcabocel         ###   ########.fr       */
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

int		parse_status(int status);
int		wait_childrens(int last_pid);

t_bool	is_valid_cmd_path(char *path, int *exit_code);
char	*get_full_cmd_path(char *cmd_name, t_env *root);
void	fork_and_exec(t_shell *shell,
			t_dynarray *cmd,
			char **argv,
			size_t start_i);

#endif