/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_wildcard.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:52:25 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 21:46:54 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_WILDCARD_H
# define STRUCT_WILDCARD_H

# include "types.h"
# include "libft_tree.h"

/**
 * @brief The wildcard structure.
 * 
 * @param is_prefix Indicates if the wildcard has a prefix.
 * @param is_suffix Indicates if the wildcard has a suffix.
 * 
 * @param is_dir Indicates if the wildcard is a directory to
 * indicate if the wildcard needs to only save directories.
 *  
 * @param pattern The pattern starting right after
 * the end of the prefix and ending right before the start
 * of the suffix.
 * 
 * @param prefix The actual prefix of the wildcard.
 * @param suffix The actual suffix of the wildcard.
 * @param base_path The path where the wildcard is located 
 * and is used to start the search.
 * @param tree The tree used to store the results of the wildcard
 * 
*/
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
void		*destroy_wildcard(t_wildcard *wildcard, t_bool tree_destroy);
t_bool		is_valid_wildcard(t_wildcard *wildcard);
t_bool		is_wildcard_prefix(const char *str, char **prefix);
t_bool		is_wildcard_suffix(const char *str, char **suffix);
size_t		get_wildcard_suffix_start(const char *str);

t_tree		*init_wildcard_tree(char *key, char *value);
t_tree		*add_wildcard_tree(t_wildcard *wildcard, t_tree *node);

#endif