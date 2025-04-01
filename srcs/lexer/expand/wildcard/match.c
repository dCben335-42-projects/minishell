#include <dirent.h>
#include "dynarray.h"
#include "libft.h"

static t_bool is_ignored_entry(const char *name, const char *pattern)
{
    if (name[0] == '.' && (!name[1] || (name[1] == '.' && !name[2])))
        return (TRUE);

    if (pattern[0] == '*' && pattern[1] == '\0' && name[0] == '.')
        return (TRUE);
    return (FALSE);
}

char **match_wildcard_entries(const char *path, const char *pattern, t_dynarray *arr)
{
    DIR *dirp;
    struct dirent *entry;
    char *copy;

    dirp = opendir(path);
    if (!dirp)
        return (NULL);
    entry = readdir(dirp);
    while (entry)
    {
        if (!is_ignored_entry(entry->d_name, pattern) && my_fnmatch(pattern, entry->d_name))
        {
            copy = ft_strdup(entry->d_name);
            if (!copy)
            {
                closedir(dirp);
                return (NULL);
            }
            set_dynarray_value(arr, arr->count, copy);
        }
        entry = readdir(dirp);
    }
    closedir(dirp);
    return ((char **)arr->data);
}
