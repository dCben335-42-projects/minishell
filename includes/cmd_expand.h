/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:19:31 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/14 18:02:17 by bcabocel         ###   ########.fr       */
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

void	*expand_word(t_shell *shell, t_dynarray *word);
void	*expand_wildcard_word(t_shell *shell, t_dynarray *word);
void	*expand_env_word(t_shell *shell, t_dynarray *word);

typedef struct t_wcard_match
{
	t_wildcard		*wildcard;
	const char		*abs_path;
	const char		*rel_path;
	const char		**segs;
	const char		**skiped_segs;
	t_bool			is_last_seg;
}	t_wcard_match;

t_bool	match_wildcard(t_wildcard *wcard,
			const char *curr_path, const char **segs);

char	*build_dir_path(const char *base,
			const char *suffix, const char **segs);
char	*build_entry_path(const char *path,
			const char *name, const char **segs);

int		resolve_entry_type(t_wcard_match *ctx, struct dirent *e);
t_bool	is_valid_entry(t_wcard_match *ctx, struct dirent *e);

t_tree	*save_entry(t_wcard_match *ctx, struct dirent *e);

#endif