#include "ast.h"

static void	add_cmd_master(t_ast_node **cmd_prev, t_dynarray *cmd_master, t_get_cmd_master *args)
{
	if (args->i == args->end)
		set_dynarray_value_secure(cmd_master,
			args->local.pos, args->local.cmd, args);
	else if (is_cmd(args, CMD_PIPE))
		get_pipe_cmd_wrapper(cmd_prev, cmd_master, args);
	else if (is_cmd(args, CMD_AND | CMD_OR | CMD_PARENTHESIS_OPEN))
		get_or_and_cmd_wrapper(cmd_prev, cmd_master, args);
	else
		*cmd_prev = args->local.cmd;
}

t_dynarray	*get_cmd_master(t_get_cmd_master *args)
{
	t_dynarray		*cmd_master;
	t_ast_node		*cmd_prev;
	t_bool			is_empty;

	cmd_master = init_dynarray_malloc(1,
			(void *(*)(void *))recursive_destroy_node);
	if (!cmd_master)
		args->has_malloc_error = TRUE;
	args->local.cmd_master = cmd_master;
	args->local.pos = 0;
	cmd_prev = NULL;
	while (args->i < args->end)
	{
		if (args->has_malloc_error)
			return (cmd_master);
		args->local.ctx = CTX_MASTER;
		if (!get_cmd(args, &is_empty))
			continue ;
		if (!args->local.cmd)
			return (cmd_master);
		add_cmd_master(&cmd_prev, cmd_master, args);
	}
	return (cmd_master);
}
