/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:28:37 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:11:22 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"
#include "messages.h"
#include "errors.h"

void	ft_pwd(t_shell *shell, char **args)
{
	(void)args;
	if (!s_ptr(shell->current_path, ERR_PWD))
	{
		shell->exit_code = 1;
		return ;
	}
	ft_putendl_fd(shell->current_path, 1);
	shell->exit_code = 0;
}
