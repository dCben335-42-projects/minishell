/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:26:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/07 15:59:01 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"


void	ft_exit(t_shell *shell, char **args)
{
	int	status;

	(void)shell;
	status = 0;
	if (args[1])
		status = ft_atoi_base(args[1], "0123456789");
	destroy_env(shell->env);
	exit(status);
}
