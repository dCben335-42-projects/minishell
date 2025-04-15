/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:54:42 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/15 16:06:14 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TREE_H
# define STRUCT_TREE_H

# include "types.h"

typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	char			*key;
	void			*value;
	void            *(*value_destroyer)(void *);
}	t_tree;

typedef t_tree	t_tree_node;

t_tree	*init_tree_node(char *key, void *value, t_bool is_nullish_value, void *(*value_destroyer)(void *));

t_tree	*add_existing_tree(t_tree *tree, char *key, void *value);
t_tree	*add_tree_node(t_tree **tree, t_tree *new);

t_tree	*get_tree_node(t_tree *tree, char *key);
t_tree	*get_tree_parent(t_tree *tree, t_tree *node);
size_t	get_size_tree(t_tree *tree);

void	*destroy_tree(t_tree *tree);
void	*destroy_tree_node(t_tree **tree, t_tree *node);

void	read_tree(t_tree *tree, const char *prefix, int f(void *, int), int fd);


// /structs/tree.h

// /structs/tree/init.c /structs/tree/destroy.c /structs/tree/add.c /structs/tree/get.c /structs/tree/read.c

#endif