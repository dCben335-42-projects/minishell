/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_wildcard.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:52:25 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/07 21:32:26 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_WILDCARD_H
# define STRUCT_WILDCARD_H

# include "types.h"
# include "dynarray.h"
# include "shell.h"
# include "libft.h"

typedef struct s_wildcard
{
	t_bool		is_error;
	t_bool 		is_prefix;
	t_bool 		is_suffix;
	t_bool 		is_dir;
	char		*pattern;
	char		*prefix;
	char		*suffix;
	char		*base_path;
	t_dynarray	arr;
}	t_wildcard;

t_wildcard	init_wildcard(const char *str, char *current_path);
void		*destroy_wildcard(t_wildcard *wildcard);


#endif