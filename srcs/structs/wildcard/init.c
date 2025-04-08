/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:51:44 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/08 21:57:22 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"

static t_bool  is_prefix(const char *str, char **prefix)
{
	size_t  i;

	i = 0;
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
	while (i > 0 && (str[i - 1] == '/' || str[i - 1] == '.'))
		i--;
	if (i != len)
		*suffix = ft_substr(str, i, len - i);
	return (i < len);
}

static char	*get_pattern(const char *str, char *prefix, char *suffix)
{
	size_t start;
	size_t end;

	start = 0;
	end = ft_strlen(str);
	if (prefix)
		start += ft_strlen(prefix);
	if (suffix)
		end -= ft_strlen(suffix);
	return (ft_substr(str, start, end - start));
}
#include "stdio.h"

static char *get_base_path(t_wildcard *wildcard, char *current_path)
{
	const char *prefix = wildcard->prefix;
	const char *args[3] = {current_path, "/", prefix};
	const char **segments = (const char **) wildcard->segments;
	size_t i;

	if (!segments)
		return (NULL);
	if (!prefix )
		return (ft_strdup(current_path));
	if (*prefix == '/')
	{
		i = 0;
		while (segments[i] && ft_strchr(segments[i], '*'))
			i++;
		if (i == 0)
			return (ft_strdup(current_path));
		char *str = ft_strsjoin(segments, i, FALSE);
		if (!str)
			return (NULL);
		printf("==========================\n");
		printf("str %s", str);
		printf("==========================\n");
	
		return (str);
	}
	return (ft_strsjoin(args, 3, FALSE));
}

static t_bool is_only_dir(const char *suffix)
{
	if (!suffix)
		return (FALSE);
	if (*suffix == '/')
		return (TRUE);
	return (FALSE);
}

t_wildcard	init_wildcard(const char *str, char *current_path)
{
	t_wildcard	wildcard;
	
	wildcard.is_error = FALSE;
	wildcard.pattern = NULL;
	wildcard.prefix = NULL;
	wildcard.suffix = NULL;
	wildcard.arr = init_dynarray(1, &basic_destroyer);
	wildcard.is_prefix = is_prefix(str, &wildcard.prefix);
	wildcard.is_suffix = is_suffix(str, &wildcard.suffix);
	wildcard.is_dir = is_only_dir(wildcard.suffix);
	wildcard.pattern = get_pattern(str, wildcard.prefix, wildcard.suffix);
	wildcard.segments = ft_split(wildcard.pattern, '/');
	wildcard.base_path = get_base_path(&wildcard, current_path);
	if ((wildcard.is_prefix && !wildcard.prefix)
		|| (wildcard.is_suffix && !wildcard.suffix)
		|| !wildcard.pattern
		|| !wildcard.base_path
		|| !wildcard.segments
	)
		destroy_wildcard(&wildcard);
	return (wildcard);
}
