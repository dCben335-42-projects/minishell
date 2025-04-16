/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:50:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/16 21:59:48 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dirent.h"
#include "libft.h"
#include <sys/stat.h>
#include <sys/types.h>

int	resolve_entry_type(struct dirent *entry, const char *path, const char **segs);
t_bool	is_valid_entry(struct dirent *entry, const char **pattern, t_bool expect_dir, t_bool is_last_segment);

int	resolve_entry_type(struct dirent *entry, const char *path, const char **segs)
{
    struct stat	entry_stat;
	char		*entry_path;

	if (entry->d_type == DT_UNKNOWN || entry->d_type == DT_LNK)
	{
		entry_path = join_entry(path, entry->d_name, segs);
        if (!entry_path || stat(entry_path, &entry_stat) == -1)
		{
			free(entry_path);
			return (DT_UNKNOWN);
		}
		free(entry_path);
		if (S_ISREG(entry_stat.st_mode))
			return (DT_REG);
		if (S_ISDIR(entry_stat.st_mode))
			return (DT_DIR);
	}
	return (entry->d_type);
}

t_bool	is_valid_entry(
	struct dirent *entry, 
	const char **pattern, 
	t_bool expect_dir, 
	t_bool is_last_segment
)
{
    const char *name = entry->d_name;
	const int	type = entry->d_type;

    if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (FALSE);
    if (is_last_segment && expect_dir && type != DT_DIR)
		return (FALSE);
	while(*pattern && (!ft_strcmp(*pattern, ".") || !ft_strcmp(*pattern, "..")))
		pattern++;
	if (**pattern != '.' && *name == '.')
        return (FALSE);
    return (ft_fnmatch(*pattern, name));
}