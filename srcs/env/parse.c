/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:59:51 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/13 19:01:46 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

static t_bool	check_key(char *key, size_t len)
{
	size_t	i;

	i = 0;
	if (key[len - 1] == '+')
		len--;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (FALSE);
	while (i < len)
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static size_t	get_equal_index(char *envp)
{
	size_t	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	return (i);
}

char	*parse_env_key(char *envp)
{
	size_t	i;

	i = get_equal_index(envp);
	if (*(envp) && *(envp) != '=' && check_key(envp, i))
	{
		if (envp[i - 1] == '+')
			return (ft_substr(envp, 0, i - 1));
		return (ft_substr(envp, 0, i));
	}
	return (NULL);
}

char	*parse_env_value(char *envp)
{
	size_t	i;

	i = get_equal_index(envp);
	if (*(envp + i) == '=' && *(envp + i + 1))
		return (ft_strdup(envp + i + 1));
	return (NULL);
}
