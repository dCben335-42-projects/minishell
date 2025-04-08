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

static void recursive_match(t_wildcard *wildcard, const char *current_path, char **segments, int index);

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

static t_bool is_valid_entry(struct dirent *entry, const char *pattern, t_bool expect_dir, t_bool is_last_segment)
{
    const char *name = entry->d_name;


    if (entry->d_type == DT_DIR && (!ft_strcmp(name, ".") || !ft_strcmp(name, "..")))
		return (FALSE);
	if (entry->d_type == DT_DIR && !is_last_segment)
		return (TRUE);
    if (expect_dir && (entry->d_type != DT_DIR && entry->d_type != DT_CHR))   
        return (FALSE);
    if (*pattern == '*' && *name == '.')
        return (FALSE);

		if (ft_strcmp(name, "X11") == 0)
	{
		printf("==========================\n");
		printf("==========================\n");
		printf("==========================\n");
		printf("name: %s\n", name);
		printf("type: %d\n", entry->d_type);
		printf("==========================\n");
		printf("==========================\n");
		printf("==========================\n");

	}
    return (ftr_fnmatch(pattern, name));
}

static char *join_paths(const char *base, const char *suffix)
{
    const size_t base_len = strlen(base);
    const size_t suffix_len = strlen(suffix);
	char *full_path;
	size_t i;
	size_t j;

    full_path = malloc(base_len + suffix_len + 2);
    if (!full_path)
		return (NULL);
	i = 0;
	j = 0;
	while (i < base_len)
    {
        full_path[i] = base[i];
        i++;
    }
    if (base_len > 0 && base[base_len - 1] != '/')
        full_path[i++] = '/';
    while (j < suffix_len)
        full_path[i++] = suffix[j++];
    full_path[i] = '\0';
    return (full_path);
}

static void process_entry(t_wildcard *wildcard, const char *current_path, char **segments, int index, struct dirent *entry, t_bool is_last)
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
		recursive_match(wildcard, next_rel, segments, index + 1);
	free(next_rel);
}

static void open_and_match_directory(t_wildcard *wildcard, const char *full_path, const char *current_path, char **segments, int index)
{
	const t_bool is_last_segment = segments[index + 1] == NULL;
	DIR				*dirp;
    struct dirent	*entry;

	dirp = opendir(full_path);
    if (!dirp)
        return;
    entry = readdir(dirp);
    while (entry)
    {
        if (is_valid_entry(entry, segments[index], wildcard->is_dir, is_last_segment))
			process_entry(wildcard, current_path, segments, index, entry, is_last_segment);
        entry = readdir(dirp);
    }
    closedir(dirp);
}

static void recursive_match(t_wildcard *wildcard, const char *current_path, char **segments, int index)
{
	char *full_path;
    if (!segments[index])
		return;
    full_path = join_paths(wildcard->base_path, current_path);
	printf("full_path: %s\n", full_path);

    if (!full_path)
		return;
    open_and_match_directory(wildcard, full_path, current_path, segments, index);
    free(full_path);
}

char **match_wildcard_entries(t_wildcard *wildcard)
{
    char **segments = ft_split(wildcard->pattern, '/');
    if (!segments)
        return (NULL);
    recursive_match(wildcard, "", segments, 0);
    ft_free_split(segments);
    return (char **)wildcard->arr.data;
}
