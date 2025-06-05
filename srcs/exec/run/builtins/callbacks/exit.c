/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:26:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 20:08:12 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"
#include "config.h"
#include "math_utils.h"
#include "utils.h"

/**
 * @brief Exits the shell with the given exit code.
 *
 * @param shell The shell instance.
 * @param args The arguments to the command.
 * 
 * @note This function prints the exit message and exits the shell
 * with the given exit code. If no exit code is provided, it uses
 * the last exit code of the shell.
 */
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
