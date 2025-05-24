#include "ast.h"

void	get_pipe_cmd_wrapper(t_ast_node **cmd_prev, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	t_ast_node	*cmd;

	cmd = args->local.cmd;
	args->local.cmd = &args->local.lcmd;
	add_child(cmd, cmd_prev, args);
	get_pipe_cmd(cmd_prev, cmd, args);
	add_child(cmd_master, &cmd, args);
}

void	get_pipe_cmd(t_ast_node **cmd_prev, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	while (args->i < args->end)
	{
		if (args->has_malloc_error)
			return ;
		args->local.ctx = CTX_PIPE;
		if (!get_cmd(args))
			continue ;
		if (is_cmd(args, CMD_SEMICOL))
			return (add_child(cmd_master, cmd_prev, args));
		if (args->i == args->end)
			return (add_child(cmd_master, &args->local.cmd, args));
		else if (is_cmd(args, CMD_PIPE))
			add_child(cmd_master, cmd_prev, args);
		else if (is_cmd(args, CMD_PARENTHESIS_OPEN))
			get_parenthesis_cmd(args, cmd_master);
		else if (!is_cmd(args, CMD_BASE))
			return (add_child(cmd_master, cmd_prev, args));
		else
			*cmd_prev = args->local.cmd;
	}
}
