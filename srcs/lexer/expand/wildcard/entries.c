#include <dirent.h>
#include "dynarray.h"
#include "libft.h"

t_bool	ftr_fnmatch(const char *pattern, const char *str)
{
	const char	*wildcard = NULL;
	const char	*last_match = NULL;

	while (*str || *pattern == '*')
	{
		if (*pattern == '*')
		{
			wildcard = pattern++;
			last_match = str;
		}
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else if (wildcard)
		{
			pattern = wildcard + 1;
			str = ++last_match;
		}
		else
			return (FALSE);
	}
	return (*pattern == '\0');
}

static t_bool is_valid_entry(const char *name, const char *pattern)
{
    if (!ft_strcmp(name, ".") || !ft_strcmp(name, ".."))
        return (FALSE);
    if (*pattern == '*' && *name == '.')
		return (FALSE);
    return (ftr_fnmatch(pattern, name));
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
        if (is_valid_entry(entry->d_name, pattern))
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
