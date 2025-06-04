/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:17:06 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 17:20:23 by bcabocel         ###   ########.fr       */
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
