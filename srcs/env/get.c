/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:59:51 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/07 14:02:36 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

char	*get_key_from_envp(char *envp)
{
	size_t	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	return (ft_substr(envp, 0, i));
}

char	*get_value_from_envp(char *envp)
{
	size_t	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	return (ft_strdup(envp + i + 1));
}