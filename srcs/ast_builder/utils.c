#include "ast.h"

int	add_previous_cmd(t_ast_node *cmd_master, t_ast_node **cmd_prev, int *i, t_ast_node *cmd)
{
	if (cmd)
	{
		(*i)--;
		free(cmd);
	}
	if (*cmd_prev)
	{
		add_child(cmd_master, *cmd_prev);
		*cmd_prev = NULL;
	}
	return (1);
}

void add_child_secure(t_ast_node *cmd_master, t_ast_node **cmd_child)
{
	if (*cmd_child)
		add_child(cmd_master, *cmd_child);
	*cmd_child = NULL;
}


int add_childs_and_increment(t_ast_node *cmd_master, t_dynamic_array *sub_cmd, int *i, int count)
{
	add_childs(cmd_master, sub_cmd);
	*i += count + 1;
	return (1);
}