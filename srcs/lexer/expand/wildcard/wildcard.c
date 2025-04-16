/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:37:52 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/16 21:58:22 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "token.h"
#include "struct_wildcard.h"
#include <stdio.h>
#include "libft.h"
#include "libft_tree.h"

static t_bool	match_wildcard(t_wildcard *wildcard, const char *curr_path, const char **segs);

static size_t	tree_valueslen(t_tree *tree, size_t sep_len, size_t *count)
{
	size_t	len;

	len = 0;
	if (!tree)
		return (0);
	len += tree_valueslen(tree->left, sep_len, count);
	if (*count == 0)
		return (len);
	len += ft_strlen(tree->value);
	if (*count > 1)
		len += sep_len;
	(*count)--;
	len += tree_valueslen(tree->right, sep_len, count);
	return (len);
}

static void	tree_valuescpy(
	t_tree *tree,
	char **cursor,
	const char *sep,
	size_t *count
)
{
	if (!tree || *count == 0)
		return ;
	tree_valuescpy(tree->left, cursor, sep, count);
	if (*count > 0)
	{
		*cursor = ft_stpcpy(*cursor, tree->value);
		if (*count > 1)
			*cursor = ft_stpcpy(*cursor, sep);
		(*count)--;
	}
	tree_valuescpy(tree->right, cursor, sep, count);
}

static char	*tree_valuesjoin(t_tree *tree, const char *sep, size_t count)
{
	char	*new;
	char	*cursor;
	size_t	sep_len;
	size_t	count_cpy;

	if (!tree || !count)
		return (NULL);
	sep_len = 0;
	if (sep)
		sep_len = ft_strlen(sep);
	printf("%zu entries\n", count);
	count_cpy = count;
	new = malloc((tree_valueslen(tree, sep_len, &count) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	cursor = new;
	tree_valuescpy(tree, &cursor, sep, &count_cpy);
	return (new);
}

/**
 * @brief Calculates the length of the keys in the tree.
 *
 * @param node The current node in the tree.
 * @param sep_len The length of the separator.
 * @param count The number of keys left to process.
 * 
 * @return The total length of the keys in the tree.
 * 
 * @note This function is recursive and traverses the tree to calculate the
 * 	length of the keys.
 * 
 * @note The function also decrements the count of keys left to process so you
 * 	 should make a copy of the count before calling this function.
*/
static size_t	tree_keyslen(t_tree *tree, size_t sep_len, size_t *count)
{
	size_t	len;

	len = 0;
	if (!tree)
		return (0);
	len += tree_keyslen(tree->left, sep_len, count);
	if (*count == 0)
		return (len);
	len += ft_strlen(tree->key);
	if (*count > 1)
		len += sep_len;
	(*count)--;
	len += tree_keyslen(tree->right, sep_len, count);
	return (len);
}

/**
 * @brief Concatenates the keys of the tree into a single string.
 *
 * @param tree The root node of the tree.
 * @param cursor The cursor to the current position in the string.
 * @param sep The separator to use between keys.
 * @param count The number of keys left to process.
 * 
 * @note The function assumes that the cursor points to a valid memory location
 *       with enough space to hold the concatenated keys.
 * 
 * @note The function also decrements the count of keys left to process so you
 * 	 should make a copy of the count before calling this function.
 */
static void	tree_keyscpy(
	t_tree *tree,
	char **cursor,
	const char *sep,
	size_t *count
)
{
	if (!tree || *count == 0)
		return ;
	tree_keyscpy(tree->left, cursor, sep, count);
	if (*count > 0)
	{
		*cursor = ft_stpcpy(*cursor, tree->key);
		if (*count > 1)
			*cursor = ft_stpcpy(*cursor, sep);
		(*count)--;
	}
	tree_keyscpy(tree->right, cursor, sep, count);
}

/**
 * @brief Joins the keys of the tree into a single string with a separator.
 *
 * @param tree The root node of the tree.
 * @param sep The separator to use between keys.
 * @return A new string containing the joined keys.
 */
char	*tree_keysjoin(t_tree *tree, const char *sep, size_t count)
{
	char	*new;
	char	*cursor;
	size_t	sep_len;
	size_t	count_cpy;

	if (!tree || !count)
		return (NULL);
	sep_len = 0;
	if (sep)
		sep_len = ft_strlen(sep);
	count_cpy = count;
	new = malloc((tree_keyslen(tree, sep_len, &count) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	cursor = new;
	tree_keyscpy(tree, &cursor, sep, &count_cpy);
	return (new);
}


static t_bool	match_wildcard_entries(t_wildcard *wildcard)
{
	const char **segs = (const char **) ft_split(wildcard->pattern, '/');
	t_bool		ret;

	if (!segs)
		return (FALSE);
	ret = match_wildcard(wildcard, "", segs);
	ft_free_split((char **)segs);
    return (ret);
}


static char	*get_wildcard(t_shell *shell, const char *value)
{
	t_wildcard	wildcard;
	char		*content;

	wildcard = init_wildcard(value, shell->current_path);
	if (!wildcard.pattern)
		return (NULL);
	if (!match_wildcard_entries(&wildcard) || !wildcard.tree)
		return (destroy_wildcard(&wildcard));
	content = tree_valuesjoin(wildcard.tree, " ", get_size_tree(wildcard.tree));
	destroy_wildcard(&wildcard);
	return (content);
}

/**
 * @brief Expands TOKEN_TEXT tokens containing wildcards.
 *
 * @param shell The shell instance.
 * @param data The token to expand. 
 */
void	*expand_wildcard_token(t_shell *shell, void *data)
{
	t_token	*token;
	char	*new_value;

	token = (t_token *)data;
	if (token->type == TOKEN_TEXT && ft_strchr(token->value, '*'))
	{
		new_value = get_wildcard(shell, token->value);
		if (!new_value)
			return (NULL);
		free(token->value);
		printf("new_value len = %zu\n", ft_strlen(new_value));
		token->value = new_value;
	}
	return (NULL);
}
