/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:48:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/11 01:38:40 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_unset(t_shell *shell, char **args)
{
	t_env	*tmp;
	size_t	i;

	i = 1;
	while (args[i])
	{
		tmp = find_env(shell->env, args[i]);
		if (tmp)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				shell->env = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			destroy_one_env(tmp);
		}
		i++;
	}
}
