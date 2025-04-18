/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_shell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:05:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:29:31 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_SHELL_H
# define STRUCT_SHELL_H

# include "struct_env.h"

typedef struct s_shell
{
	t_env	*env;
	char	*current_path;
	int		exit_code;
}	t_shell;

t_shell	init_shell(char **envp);
t_env	*init_env(char **envp);
void	*destroy_shell(t_shell *shell);

#endif