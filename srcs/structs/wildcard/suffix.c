/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suffix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:05:58 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/10 21:59:50 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "stdio.h"


static size_t skip_slashes(const char **str)
{
	size_t len;

	len = 0;
	if (**str == '/')
		len++;
	while (**str && **str == '/')
		(*str)++;
	return (len);
}

static size_t	get_suffix_len(const char *str, char **segment)
{
	size_t len;
	size_t seg_len;

	len = skip_slashes(&str);
	printf("str: %s\n", str);
	while (*segment)
	{
		seg_len = ft_strlen(*segment);
		str += seg_len;
		len += seg_len + skip_slashes(&str);
		segment++;
	}
	return (len);
}
#include <stdio.h>

static char *create(const char *str, char **split, t_bool need_last_slash)
{
	char	*dest;
	size_t	i;
	size_t	seg_len;
	
	dest = malloc(get_suffix_len(str, split) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	if (*str == '/')
		dest[i++] = '/';
	while (*split)
	{
		seg_len = ft_strlen(*split);
		ft_strlcpy(&dest[i], *split, seg_len + 1);
		i += seg_len;
		if (*(split + 1) || need_last_slash)
			dest[i++] = '/';
		split++;
	}
	dest[i] = '\0';
	return (dest);
}

static char *create_suffix(const char *str, t_bool need_last_slash)
{
	char	**split;
	char	*dest;
	
	split = ft_split(str, '/');
	if (!split)
		return (NULL);
	dest = create(str, split, need_last_slash);
	ft_free_split(split);
	return (dest);
}

size_t	get_wildcard_suffix_start(const char *str)
{
	const size_t len = ft_strlen(str);
	size_t  i;

	i = len;
	while (i > 0 && (str[i - 1] == '/' || str[i - 1] == '.'))
		i--;
	while (str[i] && str[i] != '/')
		i++;
	return (i);
}

t_bool is_suffix(const char *str, char **suffix)
{
	const size_t len = ft_strlen(str);
	const size_t i = get_wildcard_suffix_start(str);
	
	if (i != len)
		*suffix = create_suffix(&str[i], str[len - 1] == '/');
	return (i < len);
}