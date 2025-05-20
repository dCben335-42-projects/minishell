/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_shell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:05:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 04:52:48 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_SHELL_H
# define STRUCT_SHELL_H

# include "struct_env.h"
# include "struct_dynarray.h"
# include "ast_node.h"

typedef struct s_shell
{
	t_env		*env;
	t_dynarray  env_array;
	char		*current_path;
	int			exit_code;
	int 		last_pid;
	t_ast_node	*ast;
}	t_shell;

t_shell	init_shell(char **envp);
t_env	*init_env(char **envp);
void	*destroy_shell(t_shell *shell);

#endif