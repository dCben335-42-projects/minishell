#include "ast.h"

void	get_pipe_cmd_wrapper(t_ast_node *cmd,
	t_ast_node **cmd_prev, t_get_cmd_master *args, t_dynarray *cmd_master)
{
	add_child_secure(cmd, cmd_prev, args);
	get_pipe_cmd(cmd, args, cmd_prev);
	set_cmd_in_cmd_master(cmd_master, &cmd, args);
}

static void	get_pipe_cmd_next_pipe(t_ast_node **cmd_prev,
	t_ast_node *cmd, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	add_child_secure(cmd_master, cmd_prev, args);
	free(cmd);
}

static void	get_pipe_cmd_next_parenthesis(
	t_ast_node *cmd, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	destroy_node(cmd);
	get_parenthesis_cmd(args, cmd_master);
}

void	get_pipe_cmd(t_ast_node *cmd_master,
	t_get_cmd_master *args, t_ast_node **cmd_prev)
{
	t_bool		is_empty;

	while (args->i < args->end)
	{
		args->local.cmd = &args->local.lcmd;
		if (!get_cmd(args, &is_empty))
			continue ;
		if (args->local.cmd == NULL)
			return ;
		if (args->i == args->end)
			return ((void)add_child_secure(cmd_master, &args->local.cmd, args));
		else if (args->local.cmd->type == CMD_PIPE)
			get_pipe_cmd_next_pipe(cmd_prev, args->local.cmd, cmd_master, args);
		else if (args->local.cmd->type == CMD_PARENTHESIS_OPEN)
			get_pipe_cmd_next_parenthesis(args->local.cmd, cmd_master, args);
		else if (args->local.cmd->type != CMD_JOIN)
			return ((void)add_previous_cmd(cmd_master, cmd_prev, args->local.cmd, args));
		else
			*cmd_prev = args->local.cmd;
	}
}
