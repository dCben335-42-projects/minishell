/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:19:31 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/06 03:28:15 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXPAND_H
# define CMD_EXPAND_H

# include "struct_shell.h"
# include "struct_wildcard.h"
# include "struct_token.h"
# include "struct_dynarray.h"
# include "libft.h"
# include <dirent.h>

/**
 * @brief The context structure for word expansion.
 * 
 * @param arg The current expanded argument.
 * @param curr_node The current AST node being processed.
 * @param is_wildcard Indicates if the argument is a wildcard.
 * @param is_quoted Indicates if the argument is quoted.
 * 
 * @note This structure is used to keep track of the current state
 * during the saving of expanded ast nodes.
 * 
*/
typedef struct s_expand_ctx
{
	char		*arg;
	t_ast		*curr_node;
	t_bool		is_wildcard;
	t_bool		is_quoted;
}	t_expand_ctx;

t_dynarray	*expand_word(t_shell *shell, t_dynarray *word, t_dynarray *args);
char		*save_expand_entry(
				t_shell *shell,
				t_dynarray *args,
				char *value,
				t_bool is_wildcard);

t_tree		*expand_wildcard_word(t_shell *shell, char *word);
void		*expand_env_word(t_shell *shell, t_dynarray *word);
char		*expand_env_str(t_shell *shell, char **str);

/**
 * @brief The wildcard match structure.
 * 
 * @param wildcard The wildcard structure.
 * 
 * @param abs_path The absolute path of the directory which
 * is specifically used to scan the entries type
 * 
 * @param rel_path The relative path of the current entry. It is used
 * to build the path of the entry to be saved in the tree.
 * 
 * @param segs Each segment (/) of the path. It is used to
 * 
 * @param skiped_segs 
 *
 * @param is_last_seg Indicates if the current entry is the last segment
 * so that the entry can be saved in the tree. It also useful to 
 * determine if the entry need to be saved in the tree or not.
 * 
*/
typedef struct t_wcard_match
{
	t_wildcard		*wildcard;
	const char		*abs_path;
	const char		*rel_path;
	const char		**segs;
	const char		**skiped_segs;
	t_bool			is_last_seg;
}	t_wcard_match;

t_bool		match_wildcard(
				t_wildcard *wcard,
				const char *curr_path,
				const char **segs);
char		*build_dir_path(
				const char *base,
				const char *suffix,
				const char **segs);
char		*build_entry_path(
				const char *path,
				const char *name,
				const char **segs);
int			resolve_entry_type(t_wcard_match *ctx, struct dirent *e);
t_bool		is_valid_entry(t_wcard_match *ctx, struct dirent *e);
t_tree		*save_entry(t_wcard_match *ctx, struct dirent *e);

size_t		determine_env_length(const char *str, t_shell *shell);
char		*cpy_env(const char *str, char *dest, t_shell *shell);

#endif