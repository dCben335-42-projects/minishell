#ifndef ORCHESTRATOR_H
# define ORCHESTRATOR_H

# include "dynamic_array.h"
# include "token.h"
# include "libft.h"
# include "node.h"
# include <stdio.h>

t_ast_node	*find_next_cmd(t_ast_node *master_node);
void		orchestrator(t_dynamic_array *master_node_childs);

#endif