/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:35:48 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/28 15:24:56 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_redir.h"

t_dynarray  *filter_base_redir(t_shell *shell, t_ast_node *node)
{
	t_dynarray	*args;
	char		*joined_word;
	
	args = init_dynarray_malloc(1, free_value);
	if (!args->data)
		return (NULL);
	joined_word = word_join(node->content);
	if (!joined_word)
		return (destroy_dynarray(args));
	if (!expand_word(shell, node->content, args))
		return (ft_free((void **)&joined_word));
	if (!is_valid_filename(args, joined_word))
		return (destroy_dynarray(args));
	return (args);
}

t_bool	redir_append(t_shell *shell, t_ast_node *node)
{
	t_dynarray		*args;
	int				fd;
	t_bool			ret;
	
	args = filter_base_redir(shell, node);
	if (!args)
		return (FALSE);
	fd = open(args->data[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!p_int(fd, -1, args->data[0]))
		return ((t_bool) destroy_dynarray(args));
	ret = p_int(dup2(fd, STDOUT_FILENO), -1, "dup2");
	close(fd);
	destroy_dynarray(args);
	return (ret);
}


