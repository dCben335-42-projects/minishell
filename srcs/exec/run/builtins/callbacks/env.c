/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:05:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 17:37:00 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_shell.h"
#include <stdio.h>

void	ft_env(t_shell *shell, char **args)
{
	(void)args;
	read_env(shell->env, NULL);
	shell->exit_code = 0;
}
