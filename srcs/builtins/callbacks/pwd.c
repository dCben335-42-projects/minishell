/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:28:37 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/13 19:45:11 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

void	ft_pwd(t_shell *shell, char **args)
{
	(void)args;
	if (!shell->current_path)
	{
		ft_putendl_fd("minishell: pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		shell->last_exit_code = 1;
		return ;
	}
	ft_putendl_fd(shell->current_path, 1);
	shell->last_exit_code = 0;
}
