/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:05:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/14 01:37:55 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "env.h"

typedef struct s_shell
{
	t_env	*env;
	char	*current_path;
	int		exit_code;
}	t_shell;

t_shell	init_shell(char **envp);
void	*destroy_shell(t_shell *shell);

#endif