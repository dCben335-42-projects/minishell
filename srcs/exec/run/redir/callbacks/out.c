/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:34:49 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/24 20:39:42 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

t_bool	redir_out(t_shell *shell, t_ast_node *node)
{
	const char		*joined_word = word_join(node->content);
	t_dynarray		*word;
	int				fd;
	t_bool			ret;
	char			*filename;
	
	word = expand_word(shell, node->content);
	if (!word)
		return ((t_bool) ft_free((void **)&joined_word));
	if (!is_valid_filename(word, (char *)joined_word))
		return ((t_bool) destroy_expand_array(word));
	filename = get_redir_filename(word);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!p_int(fd, -1, filename))
		return ((t_bool) destroy_expand_array(word));
	ret = p_int(dup2(fd, STDOUT_FILENO), -1, "dup2");
	close(fd);
	destroy_expand_array(word);
	return (ret);
}
