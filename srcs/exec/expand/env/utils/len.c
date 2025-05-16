/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:53:13 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/16 15:54:05 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"

static size_t	get_env_len(const char *str, size_t	key_len, t_shell *shell)
{
	t_env	*env;
	char	*substr;

	if (key_len == 1 && *str == '?')
		return (ft_intlen_base(shell->exit_code, 10));
	else if (key_len)
	{
		substr = ft_substr(str, 0, key_len);
		env = get_env_node(shell->env, substr);
		free(substr);
		if (env && env->value)
			return (ft_strlen(env->value));
	}
	return (0);
}

size_t	determine_env_length(const char *str, t_shell *shell)
{
	size_t	env_len;
	size_t	total_len;
	size_t	key_len;

	total_len = 0;
	while (*str)
	{
		if (*str == '$')
		{
			key_len = parse_env_key_len(++str);
			env_len = get_env_len(str, key_len, shell);
			str += key_len - 1;
			if (env_len)
				total_len += env_len - 1;
		}
		total_len++;
		str++;
	}
	return (total_len);
}