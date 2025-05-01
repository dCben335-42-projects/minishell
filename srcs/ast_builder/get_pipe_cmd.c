#include "ast.h"

void	get_pipe_cmd_wrapper(t_ast_node *cmd,
	t_ast_node **cmd_prev, t_get_cmd_master *args, t_dynarray *cmd_master)
{
	add_child_secure(cmd, cmd_prev, args);
	get_pipe_cmd(cmd, args, cmd_prev);
	set_cmd_in_cmd_master(cmd_master, &cmd, args);
}

void	get_pipe_cmd(t_ast_node *cmd_master,
	t_get_cmd_master *args, t_ast_node **cmd_prev)
{
	t_bool		is_empty;

	while (args->i < args->end)
	{
		args->local.ctx = CTX_PIPE;
		if (!get_cmd(args, &is_empty))
			continue ;
		if (args->local.cmd == NULL)
			return ;
		if (args->i == args->end)
			return (add_child_secure(cmd_master, &args->local.cmd, args));
		else if (args->local.cmd->type == CMD_PIPE)
			add_child_secure(cmd_master, cmd_prev, args);
		else if (args->local.cmd->type == CMD_PARENTHESIS_OPEN)
			get_parenthesis_cmd(args, cmd_master);
		else if (args->local.cmd->type != CMD_JOIN)
			return (add_child_secure(cmd_master, cmd_prev, args));
		else
			*cmd_prev = args->local.cmd;
	}
}
