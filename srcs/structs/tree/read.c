/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:29:24 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 15:11:31 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_tree.h"
#include "libft.h"

void	read_tree(t_tree *tree, const char *prefix, void f(void *, int))
{
	if (!tree)
		return ;
	read_tree(tree->left, prefix, f);
	if (tree->key)
	{
		if (prefix)
			ft_putstr_fd(prefix, 1);
		ft_putstr_fd(tree->key, 1);
		if (f)
			f(tree->value, 1);
		ft_putchar_fd('\n', 1);
	}
	read_tree(tree->right, prefix, f);
}
