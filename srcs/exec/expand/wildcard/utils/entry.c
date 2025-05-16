/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/16 19:46:13 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include <sys/stat.h>

static char	*get_value(char *key, t_wildcard *wildcard)
{
	char	*new;
	char	*tmp;

	if (!key)
		return (NULL);
	new = ft_strdup(key);
	if (!new)
		return (NULL);
	if (wildcard->is_prefix)
	{
		tmp = ft_strjoin(wildcard->prefix, new);
		free(new);
		if (!tmp)
			return (NULL);
		new = tmp;
	}
	if (wildcard->is_suffix)
	{
		tmp = ft_strjoin(new, wildcard->suffix);
		free(new);
		if (!tmp)
			return (NULL);
		new = tmp;
	}
	return (new);
}

/**
 * @brief Saves the entry in the tree.
 * 
 * @param ctx The context containing the wildcard and path information.
 * @param e The entry to save.
 * 
 * @return t_tree* The tree node created for the entry, or NULL on failure.
 */
t_tree	*save_entry(t_wcard_match *ctx, struct dirent *e)
{
	char	*key;
	char	*value;
	
	key = build_entry_path(ctx->rel_path, e->d_name, ctx->segs);
	value = get_value(key, ctx->wildcard);
	return (add_wildcard_tree(ctx->wildcard, init_wildcard_tree(key, value)));
}

/**
 * @brief Resolves the entry type of a directory entry.
 * 
 * @param ctx The context containing the wildcard and path information.
 * @param e The entry to resolve.
 * 
 * @return int The resolved entry type (DT_REG, DT_DIR...).
 */
int	resolve_entry_type(t_wcard_match *ctx, struct dirent *e)
{
	struct stat	entry_stat;
	char		*entry_path;
	int			stat_result;

	if (e->d_type == DT_UNKNOWN || e->d_type == DT_LNK)
	{
		entry_path = build_entry_path(ctx->abs_path, e->d_name, ctx->segs);
		if (!entry_path)
			return (DT_UNKNOWN);
		stat_result = stat(entry_path, &entry_stat);
		free(entry_path);
		if (stat_result == -1)
			return (DT_UNKNOWN);
		if (S_ISREG(entry_stat.st_mode))
			return (DT_REG);
		if (S_ISDIR(entry_stat.st_mode))
			return (DT_DIR);
		return (DT_UNKNOWN);
	}
	return (e->d_type);
}

/**
 * @brief Checks if the entry is valid based on the context and wildcard.
 * 
 * @param ctx The context containing the wildcard and path information.
 * @param e The entry to check.
 * 
 * @return t_bool TRUE if the entry is valid, FALSE otherwise.
 */
t_bool	is_valid_entry(t_wcard_match *ctx, struct dirent *e)
{
	const char	*name = e->d_name;
	const int	type = e->d_type;

	if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (FALSE);
	if (ctx->is_last_seg && ctx->wildcard->is_dir && type != DT_DIR)
		return (FALSE);
	if (**(ctx->skiped_segs) != '.' && *name == '.')
		return (FALSE);
	return (ft_fnmatch(*(ctx->skiped_segs), name));
}
