/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:13:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/07 18:52:02 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include "stdio.h"
#include "dynarray.h"
#include "shell.h"

typedef struct s_wildcard
{
	t_bool	is_error;
	char	*pattern;
	t_bool  is_prefix;
	t_bool  is_suffix;
	char	*prefix;
	char	*suffix;
	char	*path;
	t_dynarray	arr;
}	t_wildcard;

static t_bool  is_prefix(const char *str, char **prefix)
{
	size_t  i;

	i = 0;
	*prefix = NULL;
	while (str[i] && (str[i] == '/' || str[i] == '.'))
		i++;
	if (i != 0)
		*prefix = ft_substr(str, 0, i);
	return (i > 0);
}

static t_bool is_suffix(const char *str, char **suffix)
{
	const size_t len = ft_strlen(str);
	size_t  i;

	i = len;
	*suffix = NULL;
	while (i > 0 && (str[i - 1] == '/' || str[i - 1] == '.'))
		i--;
	if (i != len)
		*suffix = ft_substr(str, i, len - i);
	return (i < len);
}


static char	*get_wildcard_pattern(const char *str, char *prefix, char *suffix)
{
	size_t start;
	size_t end;
	char *wildcard;

	start = 0;
	end = ft_strlen(str);
	if (prefix)
		start += ft_strlen(prefix);
	if (suffix)
		end -= ft_strlen(suffix);
	return (ft_substr(str, start, end - start));
}

char	*get_prefix_path(const char *current_path, const char *prefix)
{
	char	*tmp;
	const char	*args[3] = {current_path, "/", prefix};

	tmp = ft_strsjoin(args, 3, FALSE);
	if (!tmp)
		return (NULL);
	free((char *) prefix);
	return (tmp);
}


void	*destroy_wildcard_pattern(char *pattern, char *prefix, char *suffix, char *path)
{
	if (prefix && *prefix == '/')
		free(path);
	free(pattern);
	free(prefix);
	free(suffix);
	return (NULL);
}

void *handle_free(void *data)
{
	free(data);
	return (NULL);
}


void *destroy_wildcard(t_wildcard *wildcard)
{
	if (wildcard->pattern)
		free(wildcard->pattern);
	if (wildcard->prefix)
		free(wildcard->prefix);
	if (wildcard->suffix)
		free(wildcard->suffix);
	if (wildcard->path)
		free(wildcard->path);
	if (wildcard->arr.data)
		destroy_dynarray(&wildcard->arr);
	wildcard->is_error = TRUE;
	return (NULL);
}



char *get_wildcard(const char *pattern, t_shell *shell)
{
	t_wildcard	wildcard;
	char		*content;

	path = shell->current_path;
	if ((is_prefix(pattern, &prefix) && !prefix) ||
		(is_suffix(pattern, &suffix) && !suffix) ||
		(!get_wildcard_pattern(pattern, prefix, suffix)))
	{
		free(prefix);
		free(suffix);
		return (NULL);
	}
	if (prefix && *prefix == '/')
		path = get_prefix_path(shell->current_path, prefix);
	arr = init_dynarray(1, &handle_free);
	if ((!match_wildcard_entries(path, pattern, &arr) || !arr.count))
		return (destroy_wildcard_pattern(wildcard, prefix, suffix, path));
	ft_isort((char **)arr.data, arr.count, &ft_strcasecmp, FALSE);
	if (prefix)
		if (!ft_strsaddprefix(prefix, (char **)arr.data))
			return (destroy_wildcard_pattern(wildcard, prefix, suffix, path));
	if (suffix)
		if (!ft_strsaddsuffix(suffix, (char **)arr.data))
			return (destroy_wildcard_pattern(wildcard, prefix, suffix, path));
	content = ft_strsjoin((const char **)arr.data, arr.count, TRUE);
		
}