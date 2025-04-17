/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:19:31 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/17 19:16:31 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "struct_wildcard.h"
# include "libft.h"
# include "token.h"
# include <dirent.h>
# include <stdio.h>

void	*expand(t_shell *shell, t_dynarray *tokens);
void	*expand_env_token(t_shell *shell, t_token *token);
void	*expand_wildcard_token(t_shell *shell, t_token *token);

typedef struct t_wcard_match
{
	t_wildcard		*wildcard;
	const char		*abs_path;
	const char		*rel_path;
	const char		**segs;
	const char 		**skiped_segs;
	t_bool	is_last_seg;
}	t_wcard_match;

int		resolve_entry_type(t_wcard_match *ctx, struct dirent *e);
t_bool	is_valid_entry(t_wcard_match *ctx, struct dirent *e);

char	*build_dir_path(const char *base, const char *suffix, const char **segs);
char	*build_entry_path(const char *path, const char *name, const char **segs);

t_tree	*save_entry(t_wcard_match *ctx, struct dirent *e);

t_bool	match_wildcard(t_wildcard *wcard, const char *curr_path, const char **segs);

#endif