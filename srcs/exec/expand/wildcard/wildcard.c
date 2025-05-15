/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:37:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/15 16:59:07 by abonneau         ###   ########.fr       */
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
 * @param token The token to expand. 
 * 
 * @return The expanded token or NULL if an error occurred.
 */
void	*expand_wildcard_token(t_shell *shell, t_token *token)
{
	char	*new_value;

	if (token->type == TEXT && ft_strchr(token->value, '*'))
	{
		new_value = get_wildcard(shell, token->value);
		if (!new_value)
			return (NULL);
		free(token->value);
		token->value = new_value;
	}
	return (token);
}
