#include "ast.h"

void	get_or_and_cmd_wrapper(t_ast_node *cmd,
	t_get_cmd_master *args, t_ast_node **cmd_prev, t_dynamic_array *cmd_master)
{
	set_cmd_in_cmd_master(cmd_master, cmd_prev, args);
	get_or_and_cmd(cmd, args, cmd_prev);
	set_dynarray_value(
		args->local_node_info.cmd_master,
		args->local_node_info.pos,
		cmd
		);
	args->local_node_info.pos++;
}

static void	get_or_and_cmd_next_pipe(t_ast_node **cmd_prev,
	t_ast_node *cmd, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	add_previous_cmd(cmd, cmd_prev, NULL, args);
	get_pipe_cmd(cmd, args, cmd_prev);
	add_child_secure(cmd_master, &cmd, args);
}

static void	get_or_and_cmd_next_parenthesis(t_ast_node **cmd_prev,
	t_ast_node *cmd, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	free(cmd);
	add_previous_cmd(cmd_master, cmd_prev, NULL, args);
	get_parenthesis_cmd(args, cmd_master);
}

void	get_or_and_cmd(t_ast_node *cmd_master,
	t_get_cmd_master *args, t_ast_node **cmd_prev)
{
	t_ast_node	*cmd;
	t_bool		is_empty;

	while (args->i < args->end)
	{
		cmd = get_cmd(args, &is_empty);
		if (is_true_then_false(&is_empty))
			continue ;
		if (cmd == NULL)
			return ;
		if (args->i == args->end)
			return ((void)add_child_secure(cmd_master, &cmd, args));
		if (cmd->type == CMD_PIPE)
			get_or_and_cmd_next_pipe(cmd_prev, cmd, cmd_master, args);
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
			get_or_and_cmd_next_parenthesis(cmd_prev, cmd, cmd_master, args);
		else if (cmd->type == CMD_AND || cmd->type == CMD_OR)
			return ((void)add_previous_cmd(cmd_master, cmd_prev, cmd, args));
		else
			*cmd_prev = cmd;
	}
}
