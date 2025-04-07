/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:28:12 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/07 18:29:19 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

static char *create_new_path(const char *path, const char *current_path)
{
	const char *args[3] = {current_path, "/", path};
	char *tmp;

	tmp = ft_strsjoin(args, 3, FALSE);
	free((char *) path);
	return (tmp);
}

char *get_wildcard_path(const char **pattern, const char *current_path, char **extracted_path)
{
	const char	*path = extract_path(*pattern);

	if (!path)
		return (NULL);
	*pattern += ft_strlen(path);
	*extracted_path = ft_strdup(path);
	if (!*extracted_path)
		return (ft_free((void *) &path));
	if (*path == '/')
		return ((char *) path);
	return (create_new_path(path, current_path));
}