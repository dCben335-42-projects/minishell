/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_wildcard.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:52:25 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/17 20:27:52 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_WILDCARD_H
# define STRUCT_WILDCARD_H

# include "types.h"
# include "dynarray.h"
# include "shell.h"

typedef struct s_wildcard
{
	t_bool		is_prefix;
	t_bool		is_suffix;
	t_bool		is_dir;
	char		*pattern;
	char		*prefix;
	char		*suffix;
	char		*base_path;
	t_tree		*tree;
}	t_wildcard;

t_wildcard	init_wildcard(const char *str, char *current_path);
void		*destroy_wildcard(t_wildcard *wildcard);

t_bool		is_valid_wildcard(t_wildcard *wildcard);

t_bool		is_wildcard_prefix(const char *str, char **prefix);
t_bool		is_wildcard_suffix(const char *str, char **suffix);
size_t		get_wildcard_suffix_start(const char *str);

t_tree		*init_wildcard_tree(char *key, char *value);
t_tree		*add_wildcard_tree(t_wildcard *wildcard, t_tree *node);

#endif