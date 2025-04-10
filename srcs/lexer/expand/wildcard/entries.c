#include "dirent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_wildcard.h"
#include "libft.h"
#include "types.h"

#define MAX_PATH_LEN 4096
#define MAX_WILDCARD_LEN 1024
#define MAX_SEGMENTS 100

static void recursive_match(t_wildcard *wildcard, const char *current_path, char **segment);

static char *join_paths(const char *base, const char *suffix)
{
	const char *join[3] = {base, "/", suffix};

	if (!base || !suffix)
		return (NULL);
	if (!base || !*base)
		return (ft_strdup(suffix));
	if (!suffix || !*suffix)
		return (ft_strdup(base));
    return (ft_strsjoin(join, 3, FALSE));
}

static t_bool ftr_fnmatch(const char *pattern, const char *str)
{
    const char *star = NULL;
    const char *match = NULL;

    while (*str)
    {
        if (*pattern == '*')
        {
            star = pattern++;
            match = str;
        }
        else if (*pattern == *str)
        {
            pattern++;
            str++;
        }
        else if (star)
        {
            pattern = star + 1;
            str = ++match;
        }
        else
        {
            return (FALSE);
        }
    }
	// while (*pattern && *pattern == '*')
	// 	pattern++;
    return (*pattern == '\0');
}

#include <sys/stat.h>
#include <sys/types.h>

static int get_correct_type(struct dirent *entry, const char *path)
{
    struct stat	entry_stat;
	char		*entry_path;

	if (entry->d_type == DT_UNKNOWN || entry->d_type == DT_LNK)
	{
		entry_path = join_paths(path, entry->d_name);
		if (!entry_path)
			return (DT_UNKNOWN);
        if (stat(entry_path, &entry_stat) == -1)
		{
			perror("stat");
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

static t_bool is_valid_entry(struct dirent *entry, const char *pattern, t_bool expect_dir, t_bool is_last_segment)
{
    const char *name = entry->d_name;
	const int	type = entry->d_type;

    if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
		return (FALSE);
    if (is_last_segment && expect_dir && type != DT_DIR)   
        return (FALSE);
    if (*pattern == '*' && *name == '.')
        return (FALSE);
    return (ftr_fnmatch(pattern, name));
}



static void process_entry(t_wildcard *wildcard, const char *current_path, char **segment, struct dirent *entry, t_bool is_last)
{
	char *next_rel;
	
	next_rel = join_paths(current_path, entry->d_name);
    if (!next_rel)
		return ;
	if (is_last)
	{
		set_dynarray_value(&wildcard->arr, wildcard->arr.count, next_rel);
		return ;
	}
	if (entry->d_type != DT_REG) 
		recursive_match(wildcard, next_rel, (segment + 1));
	free(next_rel);
}

static void open_and_match_directory(t_wildcard *wildcard, const char *full_path, const char *current_path, char **segment)
{
	const t_bool is_last_segment = !*(segment + 1);
	DIR				*dirp;
    struct dirent	*entry;

	dirp = opendir(full_path);
    if (!dirp)
	{
		perror("opendir");
		return ;
	}
    entry = readdir(dirp);
    while (entry)
    {
		entry->d_type = get_correct_type(entry, full_path);
        if (is_valid_entry(entry, *segment, wildcard->is_dir, is_last_segment))
			process_entry(wildcard, current_path, segment, entry, is_last_segment);
        entry = readdir(dirp);
    }
    closedir(dirp);
}

static void recursive_match(t_wildcard *wildcard, const char *current_path, char **segment)
{
	char *full_path;
    if (!segment || !*segment)
		return;
    full_path = join_paths(wildcard->base_path, current_path);
    if (!full_path)
		return;
    open_and_match_directory(wildcard, full_path, current_path, segment);
    free(full_path);
}

char **match_wildcard_entries(t_wildcard *wildcard)
{
	char **segs;

	segs = ft_split(wildcard->pattern, '/');
	if (!segs)
		return (NULL);
    recursive_match(wildcard, "", segs);
	ft_free_split(segs);
    return ((char **)wildcard->arr.data);
}
