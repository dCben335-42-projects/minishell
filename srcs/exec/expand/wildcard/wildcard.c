/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:37:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/15 18:12:27 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "libft_tree.h"

static t_bool	resolve_wildcard(t_wildcard *wildcard)
{
	char		**segs;
	t_bool		ret;

	segs = ft_split(wildcard->pattern, '/');
	if (!segs)
		return (FALSE);
	ret = match_wildcard(wildcard, "", (const char **)segs);
	ft_free_split(segs);
	return (ret);
}

static char	*get_wildcard(t_shell *shell, const char *value)
{
	t_wildcard	wildcard;
	char		*content;

	wildcard = init_wildcard(value, shell->current_path);
	if (!is_valid_wildcard(&wildcard))
		return (NULL);
	if (!resolve_wildcard(&wildcard) || !wildcard.tree)
		return (destroy_wildcard(&wildcard));
	content = tree_valuesjoin(wildcard.tree, " ", get_size_tree(wildcard.tree));
	destroy_wildcard(&wildcard);
	return (content);
}

/**
 * @brief Expands TOKEN_TEXT tokens containing wildcards.
 *
 * @param shell The shell instance.
 * @param arg The pointer to the string to expand.
 * 
 * @return The expanded token or NULL if an error occurred.
 */
char	*expand_wildcard_word(t_shell *shell, char *word)
{
	char *wildcard;

	if (!word)
		return (NULL);
	wildcard = get_wildcard(shell, word);
	if (!wildcard)
		return (word);
	free(word);
	return (wildcard);
}
