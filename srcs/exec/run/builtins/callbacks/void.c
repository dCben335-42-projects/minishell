/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:02:36 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 17:07:38 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"

void	ft_void(t_shell *shell, char **args)
{
	(void)shell;
	(void)args;
	shell->exit_code = 0;
}
