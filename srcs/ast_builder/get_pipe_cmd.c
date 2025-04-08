#include "ast.h"

int get_pipe_cmd_wrapper(t_ast_node *cmd, t_ast_node **cmd_prev, t_get_cmd_master *args, t_dynamic_array *cmd_master)
{
	add_child_secure(cmd, cmd_prev, args);
	get_pipe_cmd(cmd, args, cmd_prev);
	set_cmd_in_cmd_master(cmd_master, &cmd, args);
}

int	get_pipe_cmd(t_ast_node *cmd_master, t_get_cmd_master *args, t_ast_node **cmd_prev)
{
	t_ast_node *cmd;
	t_bool		is_empty;

	while (args->i < args->end)
	{
		cmd = get_cmd(args, &is_empty);
		if (is_true_then_false(&is_empty))
			continue ;
		if (cmd == NULL)
			return (1);
		if (args->i == args->end)
			return (add_child_secure(cmd_master, &cmd, args));
		else if (cmd->type == CMD_PIPE)
		{
			add_child_secure(cmd_master, cmd_prev, args);
			free(cmd);
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
		{
			destroy_node(cmd);
			get_parenthesis_cmd(args, cmd_master);
		}
		else if (cmd->type != CMD)
			return (add_previous_cmd(cmd_master, cmd_prev, cmd, args));
		else
			*cmd_prev = cmd;
	}
	return (1);
}
