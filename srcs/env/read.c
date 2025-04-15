/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:38:20 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 16:06:07 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

void	read_env(t_env *env, const char *prefix)
{
	read_tree(env, prefix, (int (*)(void *, int)) &ft_putstr_fd, 1);
}
