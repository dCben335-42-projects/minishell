/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:26:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/11 01:19:54 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

// INT_MAX = 2147483647
// LONG_MAX = 9223372036854775807

void	ft_exit(t_shell *shell, char **args)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi_base(args[1], "0123456789");
	status = abs(status % 256);
	destroy_env(shell->env);
	exit(status);
}
