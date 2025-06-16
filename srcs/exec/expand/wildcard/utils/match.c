/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:43:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/16 19:32:04 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "libft.h"

static const char	**skip_segs(const char **segs)
{
	while (*segs && (!ft_strcmp(*segs, ".") || !ft_strcmp(*segs, "..")))
		segs++;
	return (segs);
}

static t_bool	match_entry(t_wcard_match *ctx, struct dirent *e)
{
	t_bool		ret;
	char		*e_path;

	e_path = build_entry_path(ctx->rel_path, e->d_name, ctx->segs);
	if (!e_path)
		return (FALSE);
	ret = match_wildcard(ctx->wildcard, e_path, ctx->skiped_segs + 1);
	free(e_path);
	return (ret);
}

static t_bool	process_entry(t_wcard_match *ctx, struct dirent *e)
{
	if (!is_valid_entry(ctx, e))
		return (TRUE);
	if (ctx->is_last_seg)
	{
		if (!save_entry(ctx, e))
			return (FALSE);
		return (TRUE);
	}
	if (e->d_type != DT_REG)
		return (match_entry(ctx, e));
	return (TRUE);
}

static t_bool	scan_dir(t_wcard_match *ctx)
{
	DIR				*dp;
	struct dirent	*e;

	dp = opendir(ctx->abs_path);
	if (!dp)
		return (TRUE);
	e = readdir(dp);
	while (e)
	{
		e->d_type = resolve_entry_type(ctx, e);
		if (!process_entry(ctx, e))
		{
			closedir(dp);
			return (FALSE);
		}
		e = readdir(dp);
	}
	closedir(dp);
	return (TRUE);
}

/**
 * @brief Matches a wildcard against a directory structure.
 * 
 * @param wildcard The wildcard structure.
 * @param rel_path The relative path of the directory to match.
 * @param segs The segments of the path.
 * 
 * @note This function is called recursively to match the wildcard.
 * 
 * @note The function builds the absolute path of the directory which
 * is specifically used to scan the entries type.
 * 
 * @return t_bool TRUE if the wildcard matches, FALSE otherwise.
 */
t_bool	match_wildcard(
	t_wildcard *wildcard,
	const char *rel_path,
	const char **segs
)
{
	t_wcard_match	ctx;
	t_bool			ret;
	char			*abs_path;

	abs_path = build_dir_path(wildcard->base_path, rel_path, segs);
	if (!abs_path)
		return (FALSE);
	ctx.wildcard = wildcard;
	ctx.abs_path = abs_path;
	ctx.rel_path = rel_path;
	ctx.segs = segs;
	ctx.skiped_segs = skip_segs(segs);
	ctx.is_last_seg = !*(ctx.skiped_segs + 1);
	ret = scan_dir(&ctx);
	free(abs_path);
	return (ret);
}
