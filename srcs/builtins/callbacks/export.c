/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:30:22 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/07 16:10:10 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdlib.h>

void	ft_export(t_shell *shell, char **args)
{
	char	*key;
	size_t	i;
	if (!args[1])
	{
		ft_env(shell, args);
		return ;
	}

	i = 1;
	while (args[i])
	{
		key = get_key_from_envp(args[i]);
		if (!find_env(shell->env, key))
			add_env(&shell->env, init_env(args[i]));
		else
			replace_env(shell->env, key, get_value_from_envp(args[i]));
		free(key);
		i++;
	}
}
