/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:26:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/08 17:49:04 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"
#include "messages.h"
#include "math_utils.h"

void	close_fds(void);

void	ft_exit(t_shell *shell, char **args)
{
	int		status;
	t_bool	is_number;

	status = shell->exit_code;
	ft_putendl_fd(EXIT_MSG, 1);
	if (args[1])
	{
		is_number = ft_isnumber(args[1], FALSE);
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
	destroy_shell(shell);
	ft_free_split(args);
	close_fds();
	exit(ft_abs(status % 256));
}
