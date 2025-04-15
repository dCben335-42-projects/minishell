/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:14:14 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 19:42:24 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

static const t_builtin	*get_builtin(void)
{
	static const t_builtin	map[] = {
	{ENV, &ft_env},
	{CD, &ft_cd},
	{EXPORT, &ft_export},
	{UNSET, &ft_unset},
	{PWD, &ft_pwd},
	{EXIT, &ft_exit},
	{ECHO, &ft_echo},
	{NULL, NULL}};

	return (map);
}

t_bool	is_builtin(char **args, t_shell *shell)
{
	const t_builtin	*builtin_map = get_builtin();

	while (builtin_map->name)
	{
		if (ft_strcmp(builtin_map->name, args[0]) == 0)
		{
			builtin_map->f(shell, args);
			return (TRUE);
		}
		builtin_map++;
	}
	return (FALSE);
}
