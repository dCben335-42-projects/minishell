/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:53:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/16 15:58:10 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"

static char	*copy_env_value(
	const char *str,
	size_t key_len,
	t_shell *shell,
	char *dest
)	
{
	t_env	*env;
	char	*substr;
	char	*tmp;

	if (key_len == 1 && *str == '?')
	{
		tmp = ft_itoa_base(shell->exit_code, "0123456789");
		if (!tmp)
			return (NULL);
		ft_strlcpy(dest, tmp, ft_strlen(tmp) + 1);
		free(tmp);
		return (dest);
	}
	else if (key_len)
	{
		substr = ft_substr(str, 0, key_len);
		if (!substr)
			return (NULL);
		env = get_env_node(shell->env, substr);
		free(substr);
		if (env && env->value)
			ft_strlcpy(dest, env->value, ft_strlen(env->value) + 1);
	}
	return (dest);
}

char	*cpy_env(const char *str, char *dest, t_shell *shell)
{
	size_t	i;
	size_t	key_len;

	i = 0;
	while (*str)
	{
		dest[i] = '\0';
		if (*str == '$')
		{
			key_len = parse_env_key_len(++str);
			if (key_len)
			{
				if (!copy_env_value(str, key_len, shell, dest + i))
					return (ft_free((void **)dest));
				str += key_len;
				i += ft_strlen(dest + i);
				continue ;
			}
			str--;
		}
		dest[i++] = *str++;
	}
	dest[i] = '\0';
	return (dest);
}
