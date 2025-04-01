#include "shell.h"
#include "token.h"
#include "libft.h"
#include "dynarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fnmatch.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include <stdio.h>
#include <stdlib.h>


static size_t compute_length(char **strs, size_t count, t_bool need_space)
{
	size_t	len;

	if (count == 0)
		return 0;
	len = ft_strlen(*strs);
	if (need_space && count > 1)
		len += 1; 
	return (len + compute_length(strs + 1, count - 1, need_space));
}

static void concat_strings(char *dest, char **strs, size_t count, t_bool need_space)
{
	if (count == 0)
		return;
	ft_strcat(dest, *strs);
	if (need_space && count > 1)
		ft_strcat(dest, " ");
	concat_strings(dest, strs + 1, count - 1, need_space);
}

char *handle_concat(char **data, size_t count)
{
    char *content;
	
	content = malloc(compute_length(data, count, TRUE) + 1);
    if (!content)
        return (NULL);
    content[0] = '\0';
    concat_strings(content, data, count, TRUE);
    return (content);
}

char **get_wildcard_content(const char *path, const char *pattern, t_dynarray *arr)
{
	struct dirent	*entry;
    DIR 			*dirp;
	char			*copy;

    dirp = opendir(path);
    if (!dirp)
        return (NULL);
    entry = readdir(dirp);
    while (entry) 
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		{
            entry = readdir(dirp);
            continue;
        }
        if (strcmp(pattern, "*") == 0 && entry->d_name[0] == '.')
		{
            entry = readdir(dirp);
            continue;
        }
        if (my_fnmatch(pattern, entry->d_name))
        {
            copy = strdup(entry->d_name);
            if (!copy)
            {
                closedir(dirp);
                return NULL;
            }
            set_dynarray_value(arr, arr->count, copy);
        }
        entry = readdir(dirp);
    }
    closedir(dirp);
    return ((char **)arr->data);
}

void *handle_free(void *data)
{
	free(data);
	return (NULL);
}

char *interpret_wildcard_pattern(t_shell *shell, const char *pattern)
{
	t_dynarray	arr;
	char		*content;

	arr = init_dynarray(1, (void *)(void *) &handle_free);
	if (!get_wildcard_content(shell->current_path, pattern, &arr) || !arr.count)
		return (destroy_dynarray(&arr));
	ft_isort((char **)arr.data, arr.count, &ft_strcasecmp);
	content = handle_concat((char **)arr.data, arr.count);
	destroy_dynarray(&arr);
	printf("content: %s\n", content);
	return (content);
}
void	*expand_wildcard_token(t_shell *shell, void *data)
{
	t_token	*token;

	token = (t_token *)data;
	if (token->type == TOKEN_TEXT)
	{
		free(interpret_wildcard_pattern(shell, token->value));
	}
	return (NULL);
}