#ifndef ORCHESTRATOR_H
# define ORCHESTRATOR_H

# include "struct_shell.h"
# include "ast_node.h"

typedef struct s_exec_map
{
	t_node_type	type;
	t_ast_node	*(*f)(t_shell *shell, t_ast_node *cmd);
}	t_exec_map;

void		orchestrator(t_shell *shell);
t_ast_node	*handle_cmd(t_shell *shell, t_ast_node *cmd);
t_bool		is_valid_exec_type(const t_node_type type);
t_ast_node *find_next_cmd(t_ast_node *prev_node);
t_ast_node *skip_cmd(t_ast_node *node);

t_bool		is_only_redir(t_ast_node *cmd);

t_ast_node	*exec_basic(t_shell *shell, t_ast_node *cmd);
t_ast_node	*exec_and(t_shell *shell, t_ast_node *cmd);
t_ast_node	*exec_or(t_shell *shell, t_ast_node *cmd);
t_ast_node	*exec_pipeline(t_shell *shell, t_ast_node *cmd);
t_ast_node	*exec_subshell(t_shell *shell, t_ast_node *cmd);
t_ast_node	*exec_semicolon(t_shell *shell, t_ast_node *cmd);

#endif