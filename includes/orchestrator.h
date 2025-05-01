#ifndef ORCHESTRATOR_H
# define ORCHESTRATOR_H

# include "struct_shell.h"
# include "struct_token.h"
# include "struct_env.h"
# include "libft.h"
# include "ast_node.h"
# include <stdio.h>

t_ast_node	*find_next_cmd(t_ast_node *master_node);
void		orchestrator(t_shell *shell);

#endif