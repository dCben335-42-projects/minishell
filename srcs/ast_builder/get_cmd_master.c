#include "ast.h"

void	add_cmd_master(t_get_cmd_master *args, t_ast_node *cmd,
	t_ast_node **cmd_prev, t_dynamic_array *cmd_master)
{
	if (args->i == args->end)
		set_dynarray_value_secure(cmd_master,
			args->local_node_info.pos, cmd, args);
	else if (cmd->type == CMD_PIPE)
		get_pipe_cmd_wrapper(cmd, cmd_prev, args, cmd_master);
	else if (cmd->type == CMD_AND || cmd->type == CMD_OR)
		get_or_and_cmd_wrapper(cmd, args, cmd_prev, cmd_master);
	else if (cmd->type == CMD_PARENTHESIS_OPEN)
		get_parenthesis_cmd_master_wrapper(cmd, cmd_master, cmd_prev, args);
	else
		*cmd_prev = cmd;
}

t_dynamic_array	*get_cmd_master(t_get_cmd_master *args)
{
	t_ast_node		*cmd_prev;
	t_ast_node		*cmd;
	t_dynamic_array	*cmd_master;
	t_bool			is_empty;

	cmd_master = init_dynamic_array_malloc(80,
			(void *(*)(void *))recursive_destroy_node);
	if (!cmd_master)
		*(args->has_malloc_error) = TRUE;
	args->local_node_info.cmd_master = cmd_master;
	args->local_node_info.pos = 0;
	cmd_prev = NULL;
	while (args->i < args->end)
	{
		if (*(args->has_malloc_error))
			return (cmd_master);
		cmd = get_cmd(args, &is_empty);
		if (is_true_then_false(&is_empty))
			continue ;
		if (!cmd)
			return (cmd_master);
		add_cmd_master(args, cmd, &cmd_prev, cmd_master);
	}
	return (cmd_master);
}
