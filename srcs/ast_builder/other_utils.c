#include "ast.h"

int get_cmd(t_get_cmd_master *args)
{
	args->local.cmd = &args->local.lcmd;
	get_cmd_primitive(args, &args->local.cmd);
	if (args->local.cmd)
		return (1);
	args->i++;
	return (0);
}

int	is_cmd(t_get_cmd_master *args, size_t mask)
{
	return (is_node(args->local.cmd, mask));
}

