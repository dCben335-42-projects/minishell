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


#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool my_fnmatch(const char *pattern, const char *str)
{
    if (*pattern == '\0')
        return *str == '\0';

    if (*pattern == '*') {
        while (*str) {
            if (my_fnmatch(pattern + 1, str)) {
                return true;
            }
            str++;
        }
        return my_fnmatch(pattern + 1, str);
    }

    if (*pattern == *str) {
        return my_fnmatch(pattern + 1, str + 1);
    }

    return false;
}

char *strjoin(const char *s1, const char *s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (!result) return NULL;
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *get_wildcard_content(const char *path, const char *pattern)
{
    char *content;
    char *tmp;
    DIR *dirp;
    struct dirent *entry;

    dirp = opendir(path);
    if (!dirp)
        return NULL;

    content = strdup("");
    entry = readdir(dirp);
    while (entry) 
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            entry = readdir(dirp);
            continue;
        }
        if (strcmp(pattern, "*") == 0 && entry->d_name[0] == '.') {
            entry = readdir(dirp);
            continue;
        }
        if (my_fnmatch(pattern, entry->d_name)) {
            tmp = content;
            content = strjoin(content, entry->d_name);
            free(tmp);
            tmp = content;
            content = strjoin(content, " ");
            free(tmp);
        }
        entry = readdir(dirp);
    }
    closedir(dirp);
	printf("content: %s\n", content);
    return content;
}

int	compare_strings_case_insensitive(const char *a, const char *b)
{
	int	ca;
	int	cb;

    while (*a || *b) 
	{
        ca = ft_tolower(*a);
        cb = ft_tolower(*b);
        if (ca != cb)
            return ca - cb;
        a++;
        b++;
    }
    return (ft_tolower(*a) - ft_tolower(*b));
}

void	insertion_sort(char **array, size_t	count, int (*cmp)(const char *, const char *))
{
	char	*key;
    size_t	i;
	ssize_t	j;

	i = 1;
	while (i < count)
	{
		key = array[i];
		j = i - 1;
		while (j >= 0 && cmp(array[j], key) > 0)
		{
            array[j + 1] = array[j];
            j = j - 1;
        }
		array[j + 1] = key;
		i++;
	}
}

char *sort_wildcard_content(char **content)
{
	char	**files;
	char	*sorted;
	char	*tmp;
	size_t	i;

	files = ft_split(content, ' ');
	if (!files)
		return (NULL);
	insertion_sort(files, ft_split_len(files), &compare_strings_case_insensitive);
	i = 0;
	while (files[i])
	{
		tmp = sorted;
		sorted = strjoin(sorted, files[i]);
		free(tmp);
		tmp = sorted;
		sorted = strjoin(sorted, " ");
		free(tmp);
		i++;
	}
	ft_handle_free_split(files);
	return (content);
}

void	*expand_wildcard_token(t_shell *shell, void *data)
{
	t_token	*token;

	token = (t_token *)data;
	if (token->type == TOKEN_TEXT)
	{
		free(sort_wildcard_content(get_wildcard_content(shell->current_path, ".*")));
	}
	return (NULL);
}