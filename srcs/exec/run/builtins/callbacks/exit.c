/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:26:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 16:46:29 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"
#include "messages.h"
#include "math_utils.h"
#include "utils.h"

void	ft_exit(t_shell *shell, char **args)
{
	t_bool	is_number;
	int		status;

	status = shell->exit_code;
	ft_putendl_fd(EXIT_MSG, 1);
	if (args && args[1])
	{
		is_number = ft_isnumber(args[1], TRUE);
		if (is_number && args[2])
		{
			ft_putendl_fd(ERROR_EXIT_ARGS_NUM, 2);
			return ;
		}
		if (!is_number)
		{
			ft_putendl_fd(ERROR_EXIT_NUM, 2);
			status = 2;
		}
		else
			status = ft_atol_base(args[1], BASE_10);
	}
	destroy_self(shell, args, status % 256);
}
