/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:38:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 19:11:02 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_env.h"
#include "libft.h"

static int	read_value(void *value, int fd)
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

/**
 * @brief Reads the env tree and prints the key and value of each node.
 * 
 * @param env The env tree.
 * @param prefix The prefix to search for.
 */
void	read_env(t_env *env, const char *prefix)
{
	read_tree(env, prefix, &read_value, 1);
}
