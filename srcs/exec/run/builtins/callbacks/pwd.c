/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:28:37 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 20:08:12 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"
#include "config.h"
#include "utils.h"

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
