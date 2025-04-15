/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:38:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/16 00:15:14 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

int read_value(char *value, int fd)
{
	if (value)
	{
		ft_putchar_fd('=', fd);
		ft_putchar_fd('"', fd);
		ft_putstr_fd(value, fd);
		ft_putchar_fd('"', fd);
	}
	return (1);
}

void	read_env(t_env *env, const char *prefix)
{
	read_tree(env, prefix, (int (*)(void *, int)) &read_value, 1);
}
