/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:29:24 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 16:05:47 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_tree.h"
#include "libft.h"

void	read_tree(t_tree *tree, const char *prefix, int f(void *, int), int fd)
{
	if (!tree)
		return ;
	read_tree(tree->left, prefix, f, fd);
	if (tree->key)
	{
		if (prefix)
			ft_putstr_fd(prefix, fd);
		ft_putstr_fd(tree->key, fd);
		ft_putchar_fd('=', fd);
		if (f && tree->value)
			f(tree->value, fd);
		ft_putchar_fd('\n', fd);
	}
	read_tree(tree->right, prefix, f, fd);
}
