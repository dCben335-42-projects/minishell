/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:26:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/11 20:38:11 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "messages.h"

void	ft_exit(t_shell *shell, char **args)
{
	int	status;

	status = 0;
	ft_putendl_fd(EXIT_MSG, 1);
	if (args[1] && args[2])
	{
		ft_putendl_fd(ERROR_EXIT_ARGS_NUM, 2);
		return ;
	}
	if (args[1])
	{
		if (!ft_isnumber(args[1], TRUE))
		{
			ft_putendl_fd(ERROR_EXIT_NUM, 2);
			status = 2;
		}
		else 
			status = ft_atol_base(args[1], "0123456789");
	}
		
	status = abs(status % 256);
	destroy_shell(shell);
	exit(status);
}
