/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:48:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/13 19:46:51 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include <stdio.h>

void	ft_unset(t_shell *shell, char **args)
{
	t_env	*node;
	size_t	i;

	i = 1;
	while (args[i])
	{
		node = get_env_node(shell->env, args[i]);
		if (node)
			destroy_env_node(&shell->env, node);
		i++;
	}
	shell->last_exit_code = 0;
}
