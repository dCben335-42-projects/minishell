/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 21:58:53 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/06 03:16:44 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ORCHESTRATOR_H
# define ORCHESTRATOR_H

# include "struct_shell.h"
# include "struct_ast.h"

typedef struct s_exec_map
{
	t_node_type	type;
	t_ast		*(*f)(t_shell *shell, t_ast *cmd);
}	t_exec_map;

void	orchestrator(t_shell *shell);
t_ast	*call_cmd(t_shell *shell, t_ast *cmd);
t_bool	is_valid_exec_type(const t_node_type type);
t_ast	*find_next_cmd(t_ast *prev_node);
t_ast	*skip_cmd(t_ast *node);

t_bool	is_only_redir(t_ast *cmd);

t_ast	*exec_basic(t_shell *shell, t_ast *cmd);
t_ast	*exec_and(t_shell *shell, t_ast *cmd);
t_ast	*exec_or(t_shell *shell, t_ast *cmd);
t_ast	*exec_pipeline(t_shell *shell, t_ast *cmd);
t_ast	*exec_subshell(t_shell *shell, t_ast *cmd);
t_ast	*exec_semicolon(t_shell *shell, t_ast *cmd);

#endif