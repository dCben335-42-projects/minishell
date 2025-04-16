/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entries.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:43:04 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/16 22:02:09 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dirent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_wildcard.h"
#include "libft.h"

static t_bool	match_wildcard(t_wildcard *wildcard, const char *curr_path, const char **segs);
int				resolve_entry_type(struct dirent *entry, const char *path, const char **segs);
t_bool			is_valid_entry(struct dirent *entry, const char **pattern, t_bool expect_dir, t_bool is_last_segment);

static const char **skip_segs(const char **segs)
{
	while(*segs && (!ft_strcmp(*segs, ".") || !ft_strcmp(*segs, "..")))
		segs++;
	return (segs);
}

static t_bool	match_entry(t_wildcard *wildcard, char *entry_path, const char **segs)
{	
	if (!entry_path)
		return (FALSE);
	if (!entry_path || !match_wildcard(wildcard, entry_path, (segs + 1)))
	{
		free(entry_path);
		return (FALSE);
	}
	free(entry_path);
	return (TRUE);
}

static t_bool match_dir_entrie(
	t_wildcard *wildcard,
	const char *full_path,
	const char *curr_path,
	const char **segs
)
{
	const char		**skiped_segs = skip_segs(segs);
	const t_bool	is_last = !*(skiped_segs + 1);
	DIR				*dirp;
	struct dirent	*entry;

	dirp = opendir(full_path);
    if (!dirp)
		return (TRUE);
    entry = readdir(dirp);
    while (entry)
    {
		entry->d_type = fix_type(entry, full_path, segs);
        if (is_valid_entry(entry, segs, wildcard->is_dir, is_last))
			if ((is_last && !append(entry, curr_path, segs, wildcard))
				|| (!is_last && entry->d_type != DT_REG 
					&& !match_entry(wildcard, join_entry(curr_path, entry->d_name, segs), skiped_segs)))
			{
				closedir(dirp);
				return (FALSE);
			}
        entry = readdir(dirp);
    }
    closedir(dirp);
	return (TRUE);
}

static t_bool	match_wildcard(
	t_wildcard *wildcard,
	const char *curr_path,
	const char **segs
)
{
	char *full_path;
	t_bool	ret;

    if (!segs || !*segs)
		return (FALSE);
	full_path = join_paths(wildcard->base_path, curr_path, segs);
    if (!full_path)
		return (FALSE);
	ret = match_dir_entrie(wildcard, full_path, curr_path, segs);
    free(full_path);
	return (ret);
}


