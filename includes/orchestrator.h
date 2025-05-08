#ifndef ORCHESTRATOR_H
# define ORCHESTRATOR_H

# include "struct_dynarray.h"
# include "struct_token.h"
# include "libft.h"
# include "ast_node.h"
# include <stdio.h>

t_ast_node	*find_next_cmd(t_ast_node *master_node);
void		orchestrator(t_dynarray *master_node_childs);
void		get_all_heredoc(t_ast_node *cmds);

#endif