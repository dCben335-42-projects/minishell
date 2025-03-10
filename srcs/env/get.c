/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:59:51 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/10 17:26:02 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

static size_t	get_equal_index(char *envp)
{
	size_t	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	return (i);
}

char	*get_key_from_envp(char *envp)
{
	size_t	i;

	i = get_equal_index(envp);
	if (*(envp) && *(envp) != '=')
	{
		if (envp[i - 1] == '+')
			return (ft_substr(envp, 0, i - 1));
		return (ft_substr(envp, 0, i));
	}
	return (NULL);
}

char	*get_value_from_envp(char *envp)
{
	size_t	i;

	i = get_equal_index(envp);
	if (*(envp + i) == '=' && *(envp + i + 1)) 
		return (ft_strdup(envp + i + 1));
	return (NULL);
}