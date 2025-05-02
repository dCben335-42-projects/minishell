#include "ast.h"

int get_cmd(t_get_cmd_master *args, t_bool *is_empty)
{
	args->local.cmd = &args->local.lcmd;
	get_cmd_primitive(args, is_empty, &args->local.cmd);
	if (is_true_then_false(is_empty))
		return (0);
	return (1);
}

int	is_cmd(t_get_cmd_master *args, size_t mask)
{
	return (is_node(args->local.cmd, mask));
}

