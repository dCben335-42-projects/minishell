/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:37:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/29 18:15:05 by abonneau         ###   ########.fr       */
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

static t_tree	*get_wildcard(t_shell *shell, const char *value)
{
	t_wildcard	wildcard;
	t_tree		*tree;

	wildcard = init_wildcard(value, shell->current_path);
	if (!is_valid_wildcard(&wildcard))
		return (destroy_wildcard(&wildcard, TRUE));
	if (!resolve_wildcard(&wildcard) || !wildcard.tree)
		return (destroy_wildcard(&wildcard, TRUE));
	tree = wildcard.tree;
	destroy_wildcard(&wildcard, FALSE);
	return (tree);
}

/**
 * @brief Expands TOKEN_TEXT tokens containing wildcards.
 *
 * @param shell The shell instance.
 * @param arg The pointer to the string to expand.
 * 
 * @return The expanded token or NULL if an error occurred.
 */
t_tree	*expand_wildcard_word(t_shell *shell, char *word)
{
	t_tree	*wildcard;

	if (!word)
		return (NULL);
	wildcard = get_wildcard(shell, word);
	if (!wildcard)
		return (init_wildcard_tree(ft_strdup(word), word));
	free(word);
	return (wildcard);
}
