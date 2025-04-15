/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:59:51 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/16 00:26:28 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

static t_bool	is_key(char *key, size_t len)
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

size_t	parse_env_key_len(const char *str)
{
	size_t	len;

	len = 1;
	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	if (*str == '?')
		return (1);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			break ;
		len++;
		str++;
	}
	return (len);
}

char	*parse_env_key(char *envp)
{
	size_t	i;

	i = get_equal_index(envp);
	if (*(envp) && *(envp) != '=' && is_key(envp, i))
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
