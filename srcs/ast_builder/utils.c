#include "ast.h"

int	add_previous_cmd(t_ast_node *cmd, t_ast_node **cmd_prev, int *i, t_bool decrement)
{
	if (decrement)
		(*i)--;
	if (*cmd_prev)
	{
		add_child(cmd, *cmd_prev);
		*cmd_prev = NULL;
	}
	return (1);
}
