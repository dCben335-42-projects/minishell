/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:03:02 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/10 21:55:24 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "stdio.h"

static size_t skip_slashes(const char **str)
{
	size_t len;

	len = 0;
	while (**str && **str == '/')
	{
		(*str)++;
		len++;
	}
	return (len);
}

static size_t get_suffix_len(const char *str, char **segment, const size_t index)
{
	size_t i;
	size_t len;
	size_t seg_len;

	i = 0;
	len = skip_slashes(&str);
	while (i < index)
	{
		seg_len = ft_strlen(segment[i]);
		str += seg_len;
		len += seg_len + skip_slashes(&str);
		i++;
	}
	return (len);
}


t_bool	is_prefix(const char *str, char **prefix)
{
	char	**segs;
	size_t	i;
	size_t len;

	segs = ft_split(str, '/');
	i = 0;
	if (!segs)
		return (FALSE);
	while (segs[i] && !ft_strchr(segs[i], '*'))
		i++;
	len = get_suffix_len(str, segs, i);
	if (len)
		*prefix = ft_substr(str, 0, len);
	ft_free_split(segs);
	return (len > 0);
}
