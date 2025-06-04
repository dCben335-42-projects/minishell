/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suffix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:05:58 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 03:11:22 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include <stdio.h>

static size_t	skip_slashes(const char **str)
{
	size_t	len;

	len = 0;
	if (**str == '/')
		len++;
	while (**str && **str == '/')
		(*str)++;
	return (len);
}

static size_t	get_suffix_len(const char *str, char **segment)
{
	size_t	len;
	size_t	seg_len;

	len = skip_slashes(&str);
	while (*segment)
	{
		seg_len = ft_strlen(*segment);
		str += seg_len;
		len += seg_len + skip_slashes(&str);
		segment++;
	}
	return (len);
}

static char	*create_suffix(
	const char *str,
	char **segs,
	t_bool need_last_slash
)
{
	size_t	i;
	size_t	seg_len;
	char	*dest;

	dest = malloc((get_suffix_len(str, segs) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	if (*str == '/')
		dest[i++] = '/';
	dest[i] = '\0';
	while (*segs)
	{
		seg_len = ft_strlen(*segs);
		ft_strlcpy(&dest[i], *segs, seg_len + 1);
		i += seg_len;
		if (*(segs + 1) || need_last_slash)
			dest[i++] = '/';
		segs++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * @brief Gets the starting index of the wildcard suffix in the given string.
 * 
 * @param str The string to search for a wildcard suffix.
 * @return size_t The starting index of the wildcard suffix.
 * 
 * This function iterates through the string from the end to find the starting
 * index of the wildcard suffix. It counts the number of dots and slashes
 * encountered, and stops when it finds more than two dots or reaches a
 * non-dot/slash character.
 * 
 * @note It skips any trailing slashes at the begining of the suffix.
 */
size_t	get_wildcard_suffix_start(const char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			i;
	size_t			dot_count;

	i = len;
	dot_count = 0;
	while (i > 0 && (str[i - 1] == '/' || str[i - 1] == '.'))
	{
		if (str[i - 1] == '.')
			dot_count++;
		else
			dot_count = 0;
		if (dot_count > 2)
			break ;
		i--;
	}
	while (str[i] && str[i] != '/')
		i++;
	return (i);
}

/**
 * @brief Checks if the given string has a wildcard suffix and extracts it.
 * 
 * @param str The string to check for a wildcard suffix.
 * @param suffix A pointer to store the extracted suffix.
 * @return t_bool TRUE if the string has a wildcard suffix, FALSE otherwise.
 * 
 * This function checks if the given string has a wildcard suffix (i.e., a
 * substring that starts with a wildcard character). If a wildcard suffix is
 * found, it extracts it and stores it in the provided pointer.
 */
t_bool	is_wildcard_suffix(const char *str, char **suffix)
{
	const size_t	len = ft_strlen(str);
	const size_t	i = get_wildcard_suffix_start(str);
	char			**segs;

	if (i != len)
	{
		segs = ft_split(&str[i], "/");
		if (segs)
		{
			*suffix = create_suffix(&str[i], segs, str[len - 1] == '/');
			ft_strsfree(segs);
		}
	}
	return (i < len);
}
