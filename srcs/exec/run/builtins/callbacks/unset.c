/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:48:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/06 18:45:27 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"

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
	shell->exit_code = 0;
	destroy_dynarray(&shell->env_array);
	shell->env_array = env_to_array(shell->env);
}
