#include "dirent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_wildcard.h"
#include "libft.h"
#include "types.h"
#include <sys/stat.h>
#include <sys/types.h>

static char	**recursive_match(t_wildcard *wildcard, const char *curr_path, char **segment);


char *join_segs(char *new, char **segs)
{
	char	*tmp;

	if (!new || !segs)
		return (NULL);
	while (*segs && (!ft_strcmp(*segs, ".") || !ft_strcmp(*segs, "..")))
	{
		tmp = ft_strsjoin((const char *[3]){new, *segs, "/"}, 3, FALSE);
		free(new);
		if (!tmp)
			return (NULL);
		new = tmp;
		segs++;
	}
	return (new);
}

static char *join_paths(const char *base, const char *suffix, char **segs)
{
	const char *join[4] = {base, "/", suffix, "/"};
	char	*new;

	if (!base || !suffix)
		return (NULL);
	if (!*base)
		return (ft_strdup(suffix));
	if (!*suffix)
		return (ft_strdup(base));
    new = ft_strsjoin(join, 4, FALSE);
	return (join_segs(new, segs));
}

char *join_entry(const char *curr_path, const char *name, char **segs)
{
	char	*new;
	char 	*tmp;

	if (!curr_path || !name)
		return (NULL);
	if (!*curr_path)
		return (ft_strdup(name));
	new = ft_strjoin(curr_path, "/");
	new = join_segs(new, segs);
	if (!new)
		return (NULL);
	tmp = ft_strjoin(new, name);
	free(new);
	if (!tmp)
		return (NULL);
	new = tmp;
	return (new);
}


static inline int get_correct_type(struct dirent *entry, const char *path, char **segs)
{
    struct stat	entry_stat;
	char		*entry_path;

	if (entry->d_type == DT_UNKNOWN || entry->d_type == DT_LNK)
	{
		entry_path = join_entry(path, entry->d_name, segs);
		if (!entry_path)
			return (DT_UNKNOWN);
        if (stat(entry_path, &entry_stat) == -1)
		{
			free(entry_path);
			return (DT_UNKNOWN);
		}
		free(entry_path);
		if (S_ISREG(entry_stat.st_mode))
			return (DT_REG);
		if (S_ISDIR(entry_stat.st_mode))
			return (DT_DIR);
		return (DT_UNKNOWN);
	}
	return (entry->d_type);
}

static t_bool	is_last_segment(char **segs)
{
	while(*segs && (!ft_strcmp(*segs, ".") || !ft_strcmp(*segs, "..")))
		segs++;
	return (!*(segs + 1));
}

static t_bool is_valid_entry(struct dirent *entry, char **pattern, t_bool expect_dir, t_bool is_last_segment)
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

static char **process_entry(t_wildcard *wildcard, const char *curr_path, char **segs, struct dirent *entry, t_bool is_last)
{
	char *next_rel;
	
	if (is_last)
	{
		next_rel = join_entry(curr_path, entry->d_name, segs);
		if (!next_rel)
			return (NULL);
		set_dynarray_value(&wildcard->arr, wildcard->arr.count, next_rel);
		return ((char **)wildcard->arr.data);
	}
	if (entry->d_type != DT_REG) 
	{
		next_rel = join_entry(curr_path, entry->d_name, segs);
		if (!next_rel)
			return (NULL);
		while(*segs && (!ft_strcmp(*segs, ".") || !ft_strcmp(*segs, "..")))
			segs++;
		if (!recursive_match(wildcard, next_rel, (segs + 1)))
		{
			free(next_rel);
			return (NULL);
		}
		free(next_rel);
	}
	return ((char **)wildcard->arr.data);
}

static char	**open_and_match_directory(t_wildcard *wildcard, const char *full_path, const char *curr_path, char **segs)
{
	const t_bool is_last_seg = is_last_segment(segs);
	DIR				*dirp;
    struct dirent	*entry;

	dirp = opendir(full_path);
    if (!dirp)
		return ((char **)wildcard->arr.data);
    entry = readdir(dirp);
    while (entry)
    {
		entry->d_type = get_correct_type(entry, full_path, segs);
        if (is_valid_entry(entry, segs, wildcard->is_dir, is_last_seg))
		{
			if (!process_entry(wildcard, curr_path, segs, entry, is_last_seg))
			{
				closedir(dirp);
				return (NULL);
			}
		}
        entry = readdir(dirp);
    }
    closedir(dirp);
	return ((char **)wildcard->arr.data);
}

static char	**recursive_match(t_wildcard *wildcard, const char *curr_path, char **segs)
{
	char *full_path;
	char **ret;

    if (!segs || !*segs)
		return (NULL);
	full_path = join_paths(wildcard->base_path, curr_path, segs);
    if (!full_path)
		return (NULL);
	ret = open_and_match_directory(wildcard, full_path, curr_path, segs);
    free(full_path);
	return (ret);
}

char **match_wildcard_entries(t_wildcard *wildcard)
{
	char **segs;
	char **ret;

	segs = ft_split(wildcard->pattern, '/');
	if (!segs)
		return (NULL);
	ret = recursive_match(wildcard, "", segs);
	ft_free_split(segs);
    return (ret);
}
