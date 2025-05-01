#include "ast.h"

void	get_or_and_cmd_wrapper(t_ast_node *cmd,
	t_get_cmd_master *args, t_ast_node **cmd_prev, t_dynarray *cmd_master)
{
	set_cmd_in_cmd_master(cmd_master, cmd_prev, args);
	get_or_and_cmd(cmd, args, cmd_prev);
	set_dynarray_value(
		args->local.cmd_master,
		args->local.pos,
		cmd
		);
	args->local.pos++;
}

static void	get_or_and_cmd_next_pipe(t_ast_node **cmd_prev, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	t_ast_node	*cmd;

	cmd = args->local.cmd;
	args->local.cmd = &args->local.lcmd;
	add_child_secure(cmd, cmd_prev, args);
	get_pipe_cmd(cmd, args, cmd_prev);
	add_child_secure(cmd_master, &cmd, args);
}

static void	get_or_and_cmd_next_parenthesis(t_ast_node **cmd_prev, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	add_child_secure(cmd_master, cmd_prev, args);
	get_parenthesis_cmd(args, cmd_master);
}

void	get_or_and_cmd(t_ast_node *cmd_master,
	t_get_cmd_master *args, t_ast_node **cmd_prev)
{
	t_bool		is_empty;

	while (args->i < args->end)
	{
		args->local.ctx = CTX_AND_OR;
		if (!get_cmd(args, &is_empty))
			continue ;
		if (args->local.cmd == NULL)
			return ;
		if (args->i == args->end)
			return (add_child_secure(cmd_master, &args->local.cmd, args));
		if (args->local.cmd->type == CMD_PIPE)
			get_or_and_cmd_next_pipe(cmd_prev, cmd_master, args);
		else if (args->local.cmd->type == CMD_PARENTHESIS_OPEN)
			get_or_and_cmd_next_parenthesis(cmd_prev, cmd_master, args);
		else if (args->local.cmd->type == CMD_AND || args->local.cmd->type == CMD_OR)
			return (add_child_secure(cmd_master, cmd_prev, args));
		else
			*cmd_prev = args->local.cmd;
	}
}
