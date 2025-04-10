/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:51:44 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/10 21:57:23 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_wildcard.h"
#include "libft.h"
#include "stdio.h"

static char	*get_pattern(const char *str, char *prefix, char *suffix)
{
	size_t start;
	size_t end;

	start = 0;
	end = ft_strlen(str);
	if (prefix)
		start += ft_strlen(prefix);
	if (suffix)
		end = get_wildcard_suffix_start(str);
	return (ft_substr(str, start, end - start));
}

static char *get_base_path(char *prefix, char *current_path)
{
	const char *args[3] = {current_path, "/", prefix};

	if (!prefix)
		return (ft_strdup(current_path));
	if (*prefix == '/')
		return (ft_strdup(prefix));
	return (ft_strsjoin(args, 3, FALSE));
}

t_wildcard *fill_wildcard(t_wildcard *wildcard, const char *str, char *current_path)
{
	wildcard->arr = init_dynarray(1, &basic_destroyer);
	if (!wildcard->arr.data)
		return (destroy_wildcard(wildcard));
	wildcard->is_prefix = is_prefix(str, &wildcard->prefix);
	wildcard->is_suffix = is_suffix(str, &wildcard->suffix);
	wildcard->is_dir = wildcard->is_suffix;
	wildcard->pattern = get_pattern(str, wildcard->prefix, wildcard->suffix);
	wildcard->base_path = get_base_path(wildcard->prefix, current_path);
	if ((wildcard->is_prefix && !wildcard->prefix)
		|| (wildcard->is_suffix && !wildcard->suffix)
		|| !wildcard->pattern
		|| !wildcard->base_path
	)
		return (destroy_wildcard(wildcard));
	return (wildcard);
}

t_wildcard	init_wildcard(void)
{
	t_wildcard	wildcard;
	
	wildcard.is_prefix = FALSE;
	wildcard.is_suffix = FALSE;
	wildcard.is_dir = FALSE;
	wildcard.pattern = NULL;
	wildcard.prefix = NULL;
	wildcard.suffix = NULL;
	wildcard.base_path = NULL;
	return (wildcard);
}
