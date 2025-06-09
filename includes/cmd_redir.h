/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:34:29 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 16:01:07 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_REDIR_H
# define CMD_REDIR_H

# include "struct_shell.h"
# include "libft_tree.h"
# include "cmd_expand.h"
# include "fcntl.h"
# include "unistd.h"
# include "utils.h"

typedef struct s_redir_map
{
	t_node_type	type;
	t_bool		(*f)(t_shell	*shell, t_ast	*node);
}	t_redir_map;

t_bool		redirect(t_shell *shell, t_dynarray *cmd);
t_bool		is_only_redir(t_ast *cmd);

t_dynarray	*filter_base_redir(t_shell *shell, t_ast *node, t_dynarray *args);
t_bool		is_valid_filename(t_dynarray *arr, char *joined_word);

t_bool		redir_out(t_shell *shell, t_ast *node);
t_bool		redir_in(t_shell *shell, t_ast *node);
t_bool		redir_append(t_shell *shell, t_ast *node);
t_bool		redir_heredoc(t_shell *shell, t_ast *node);

#endif
