/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:10:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/14 18:03:22 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"


// /**
//  * @brief Expands the tokens in the shell.
//  *
//  * @param shell The shell instance.
//  * @param tokens The tokens to expand.
//  * 
//  * @return The expanded tokens or NULL if an error occurred.
//  */
// void	*expand(t_shell *shell, t_dynarray *args)
// {
// 	if (!expand_env(shell, args))
// 		return (destroy_dynarray(args));
// 	if (!expand_wildcard(shell, args))
// 		return (destroy_dynarray(args));
// 	return (args);
// }

// static t_bool  has_word_type(t_dynarray *word, const t_node_type type)
// {
// 	t_ast_node	*node;
// 	t_uint		i;

// 	i = 0;
// 	while (i < word->count)
// 	{
// 		node = (t_ast_node *)get_dynarray_value(word, i);
// 		if (node->type == type)
// 			return (TRUE);
// 		i++;
// 	}
// 	return (FALSE);
// }

void *expand_word(t_shell *shell, t_dynarray *word)
{
	expand_env_word(shell, word);
	return (word);
}