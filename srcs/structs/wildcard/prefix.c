/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:03:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 03:11:22 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "stdio.h"

static size_t	skip_slashes(const char **str)
{
	size_t	len;

	len = 0;
	while (**str && **str == '/')
	{
		(*str)++;
		len++;
	}
	return (len);
}

static size_t	get_suffix_len(
	const char *str,
	char **segs,
	const size_t index
)
{
	size_t	i;
	size_t	len;
	size_t	seg_len;

	i = 0;
	len = skip_slashes(&str);
	while (i < index)
	{
		seg_len = ft_strlen(segs[i]);
		str += seg_len;
		len += seg_len + skip_slashes(&str);
		i++;
	}
	return (len);
}

/**
 * @brief Checks if the given string has a wildcard prefix and extracts it.
 * 
 * @param str The string to check for a wildcard prefix.
 * @param prefix A pointer to store the extracted prefix.
 * @return t_bool TRUE if the string has a wildcard prefix, FALSE otherwise.
 * 
 * This function checks if the given string has a wildcard prefix (i.e., a
 * substring that starts with a wildcard character). If a wildcard prefix is
 * found, it extracts it and stores it in the provided pointer.
 */
t_bool	is_wildcard_prefix(const char *str, char **prefix)
{
	char	**segs;
	size_t	i;
	size_t	len;

	segs = ft_split(str, "/");
	i = 0;
	if (!segs)
		return (FALSE);
	while (segs[i] && !ft_strchr(segs[i], -'*'))
		i++;
	len = get_suffix_len(str, segs, i);
	if (len)
		*prefix = ft_substr(str, 0, len);
	ft_strsfree(segs);
	return (len > 0);
}
