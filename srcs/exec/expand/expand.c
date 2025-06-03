/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:10:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/03 17:35:23 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "utils.h"
#include "libft_tree.h"
#include "parsing.h"
#include "ast.h"
#include "cmd_redir.h"

void	negate_wildcard(char **str);

// static char *join_token(t_token *token, char *value, t_bool *is_wildcard, t_bool *is_quoted)
// {
// 	char	*tmp;
// 	t_token_type	type;

// 	type = token->type;
// 	if (type & WILDCARD)
// 		*is_wildcard = TRUE;
// 	if (type & (WILDCARD | TEXT))
// 		negate_wildcard(&token->value);
// 	if (type & (QUOTED_TEXT | QUOTED_EXPAND))
// 		*is_quoted = TRUE;
// 	tmp = ft_strjoin(value, token->value);
// 	free(value);
// 	if (!tmp)
// 		return (NULL);
// 	return (tmp);
// }

// static t_dynarray	*join_word_tokens(t_shell *shell, t_dynarray *tokens, t_dynarray *args)
// {
// 	t_token	*token;
// 	char	*value;
// 	t_bool  is_wildcard;
// 	t_bool  is_quoted;
// 	t_uint	i;

// 	i = 0;
// 	value = ft_strdup("");
// 	if (!value)
// 		return (NULL);
// 	is_wildcard = FALSE;
// 	is_quoted = FALSE;
// 	while (i < tokens->count)
// 	{
// 		token = get_dynarray_value(tokens, i);
// 		if (token->type == M_EOF || token->type == M_SPACE)
// 			value = save_expand_entry(shell, args, value, &is_wildcard, &is_quoted);
// 		else
// 			value = join_token(token, value, &is_wildcard, &is_quoted);
// 		if (!value)
// 			return (NULL);
// 		i++;
// 	}
// 	free(value);
// 	return (args);
// }


void *join_all(t_shell *shell, t_dynarray *word, t_dynarray *args);

/**
 * @brief Expands a word in the shell context.
 * 
 * This function checks if the word is an environment variable or a wildcard.
 *
 * @param shell The shell context containing environment variables.
 * @param word The word to be expanded, represented as a dynamic array.
 * @param args The array to store the expanded arguments.
 * 
 * @return The last args element or NULL if an error occurs.
*/
t_dynarray	*expand_word(t_shell *shell, t_dynarray *word, t_dynarray *args)
{
	if (!expand_env_word(shell, word))
		return (NULL);
	return (join_all(shell, word, args));
}
