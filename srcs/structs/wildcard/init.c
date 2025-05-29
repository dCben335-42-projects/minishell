/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:51:44 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/29 15:48:29 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "stdio.h"

static char	*get_pattern(const char *str, char *prefix, char *suffix)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(str);
	if (prefix)
		start += ft_strlen(prefix);
	if (suffix)
		end = get_wildcard_suffix_start(str);
	return (ft_substr(str, start, end - start));
}

static char	*get_base_path(char *prefix, char *current_path)
{
	const char	*args[] = {current_path, "/", prefix};

	if (!prefix)
	{
		if (!current_path)
			return (NULL);
		return (ft_strdup(current_path));
	}
	if (*prefix == '/')
		return (ft_strdup(prefix));
	return (ft_strsjoin(args, 3, FALSE));
}

/**
 * @brief Initializes a wildcard structure based on the given string and path.
 * 
 * @param str The string to initialize the wildcard from.
 * @param current_path The current path to use for base path calculation.
 * @return t_wildcard The initialized wildcard structure.
 * 
 * This function initializes a t_wildcard structure by checking if the given
 * string has a prefix or suffix, extracting the pattern, and determining the
 * base path. If any of the components are invalid, it destroys the wildcard
 * structure and returns an empty one.
*/
t_wildcard	init_wildcard(const char *str, char *current_path)
{
	t_wildcard	wildcard;

	wildcard.prefix = NULL;
	wildcard.suffix = NULL;
	wildcard.tree = NULL;
	wildcard.is_prefix = is_wildcard_prefix(str, &wildcard.prefix);
	wildcard.is_suffix = is_wildcard_suffix(str, &wildcard.suffix);
	wildcard.is_dir = wildcard.is_suffix;
	wildcard.pattern = get_pattern(str, wildcard.prefix, wildcard.suffix);
	wildcard.base_path = get_base_path(wildcard.prefix, current_path);
	return (wildcard);
}
