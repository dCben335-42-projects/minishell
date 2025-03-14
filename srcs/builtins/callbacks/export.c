/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:30:22 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/14 01:37:55 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdio.h>
#include "messages.h"

static void	process_env(t_shell *shell, char *key, char *arg)
{
	const t_env	*matched_env = get_env_node(shell->env, key);
	char		*value;
	char		*complete_value;
	
	if (!matched_env)
	{
		add_env(&shell->env, init_env_node(arg));
		return ;
	}
	value = parse_env_value(arg);
	if (!value)
		value = ft_strdup("");
	if (!value)
	{
		perror(ERR_CD);
		return ;
	}
	complete_value = value;
	if ((arg[ft_strlen(key)] == '+'))
	{
		complete_value = ft_strjoin(matched_env->value, value);
		free(value);
	}
	if (complete_value && !add_existing_env(shell->env, key, complete_value))
		free(complete_value);
}

static t_bool	is_valid_export(t_shell *shell, char **args)
{
	char	*key;
	size_t	i;
	t_bool	is_valid;

	i = 1;
	is_valid = TRUE;
	while (args[i])
	{
		key = parse_env_key(args[i]);
		if (!key)
		{
			is_valid = FALSE;
			printf("export: '%s': not a valid identifier\n", args[i]);
		}
		else
			process_env(shell, key, args[i]);
		free(key);
		i++;
	}
	return (is_valid);
}

void	ft_export(t_shell *shell, char **args)
{
	if (!args[1])
		read_env(shell->env, EXPORT_PREFIX);
	else if (!is_valid_export(shell, args))
	{
		shell->exit_code = 1;
		return ;
	}
	shell->exit_code = 0;
}
