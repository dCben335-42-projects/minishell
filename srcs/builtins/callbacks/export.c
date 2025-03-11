/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:30:22 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/11 19:37:38 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdio.h>
#include "messages.h"

static void	handle_export(t_shell *shell, char *key, char *arg)
{
	const t_env	*matched_env = find_env(shell->env, key);
	char		*value;
	char		*complete_value;
	
	if (!matched_env)
	{
		add_env(&shell->env, init_env(arg));
		return ;
	}
	value = get_value_from_envp(arg);
	if (!value)
		value = ft_strdup("");
	if (!value)
	{
		perror(ERROR_CD);
		return ;
	}
	complete_value = value;
	if ((arg[ft_strlen(key)] == '+'))
	{
		complete_value = ft_strjoin(matched_env->value, value);
		free(value);
	}
	if (complete_value && !replace_env(shell->env, key, complete_value))
		free(complete_value);
}

void	ft_export(t_shell *shell, char **args)
{
	char	*key;
	size_t	i;

	if (!args[1])
	{
		read_env(shell->env, "declare -x ");
		return ;
	}
	i = 1;
	while (args[i])
	{
		key = get_key_from_envp(args[i]);
		if (!key)
			printf("export: '%s': not a valid identifier\n", args[i]);
		else
			handle_export(shell, key, args[i]);
		free(key);
		i++;
	}
}
