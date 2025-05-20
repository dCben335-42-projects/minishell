/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:34:49 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/20 14:34:50 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

t_bool	redir_out(t_shell *shell, t_ast_node *node)
{
	const char		*joined_word = word_join(node->content);
	t_tree			*tree;
	int				fd;
	t_bool			ret;

	tree = expand_word(shell, node->content);
	ret = TRUE;
	if (!tree)
		return ((t_bool) ft_free((void **)&joined_word));
	if (!is_valid_filename(tree, (char *)joined_word))
		return ((t_bool) destroy_tree(tree));
	fd = open(tree->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!p_int(fd, -1, tree->value))
		return ((t_bool) destroy_tree(tree));
	ret = p_int(dup2(fd, STDOUT_FILENO), -1, "dup2");
	close(fd);
	destroy_tree(tree);
	return (ret);
}
