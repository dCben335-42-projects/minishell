/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:43:40 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/16 21:49:53 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_segs(char *new, const char **segs)
{
	char	*tmp;

	if (!new || !segs)
		return (NULL);
	while (*segs && (!ft_strcmp(*segs, ".") || !ft_strcmp(*segs, "..")))
	{
		tmp = ft_strsjoin((const char *[3]){new, *segs, "/"}, 3, FALSE);
		free(new);
		if (!tmp)
			return (NULL);
		new = tmp;
		segs++;
	}
	return (new);
}

char	*join_paths(const char *base, const char *suffix, const char **segs)
{
	const char	*join[4] = {base, "/", suffix, "/"};
	char		*new;

	if (!base || !suffix)
		return (NULL);
	if (!*base)
		return (ft_strdup(suffix));
	if (!*suffix)
		return (ft_strdup(base));
    new = ft_strsjoin(join, 4, FALSE);
	return (join_segs(new, segs));
}

char	*join_entry(const char *curr_path, const char *name, const char **segs)
{
	char	*new;
	char 	*tmp;

	if (!curr_path || !name)
		return (NULL);
	if (!*curr_path)
		return (ft_strdup(name));
	new = ft_strjoin(curr_path, "/");
	new = join_segs(new, segs);
	if (!new)
		return (NULL);
	tmp = ft_strjoin(new, name);
	free(new);
	if (!tmp)
		return (NULL);
	new = tmp;
	return (new);
}
