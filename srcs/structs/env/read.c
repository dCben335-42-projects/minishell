/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:38:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 20:40:31 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_env.h"
#include "libft.h"
#include "config.h"

static void	read_exported_env(t_env *node)
{
	const int	fd = STDOUT_FILENO;

	ft_putstr_fd(EXPORT_PREFIX" ", fd);
	ft_putstr_fd(node->key, fd);
	if (node->value)
	{
		ft_putchar_fd('=', fd);
		ft_putchar_fd('"', fd);
		ft_putstr_fd(node->value, fd);
		ft_putchar_fd('"', fd);
	}
	ft_putchar_fd('\n', fd);
}

static void	read_base_env(t_env *node)
{
	const int	fd = STDOUT_FILENO;

	if (node->value)
	{
		ft_putstr_fd(node->key, fd);
		ft_putchar_fd('=', fd);
		ft_putchar_fd('"', fd);
		ft_putstr_fd(node->value, fd);
		ft_putchar_fd('"', fd);
		ft_putchar_fd('\n', fd);
	}
}

/**
 * @brief Reads the env tree and prints the key and value of each node.
 * 
 * @param env The env tree.
 * @param for_export If true, the output is formatted for export by
 * adding the `export` prefix. (no `declare -x` prefix because
 * it is note recognized by this shell) 
 *
*/
void	read_env(t_env *env, t_bool for_export)
{
	if (for_export)
		read_tree(env, &read_exported_env);
	else
		read_tree(env, &read_base_env);
}
