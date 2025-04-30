#include "ast.h"

int get_cmd(t_get_cmd_master *args, t_bool *is_empty)
{
	get_cmd_primitive(args, is_empty, &args->local.cmd);
	if (is_true_then_false(is_empty))
		return (0);
	return (1);
}
