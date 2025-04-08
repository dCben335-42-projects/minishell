#include "ast.h"

void	get_or_and_cmd_wrapper(t_ast_node *cmd,
	t_get_cmd_master *args, t_ast_node **cmd_prev, t_dynamic_array *cmd_master)
{
	set_cmd_in_cmd_master(cmd_master, cmd_prev, args);
	get_or_and_cmd(cmd, args, cmd_prev);
	set_dynarray_value(
		args->local_node_info.cmd_master,
		*(args->local_node_info.pos),
		cmd
		);
	(*args->local_node_info.pos)++;
}

int	get_or_and_cmd(t_ast_node *cmd_master,
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
			return (1);
		if (args->i == args->end)
			return (add_child_secure(cmd_master, &cmd, args));
		if (cmd->type == CMD_PIPE)
		{
			add_previous_cmd(cmd, cmd_prev, NULL, args);
			if (get_pipe_cmd(cmd, args, cmd_prev) == 1)
				add_child_secure(cmd_master, &cmd, args);
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
		{
			free(cmd);
			add_previous_cmd(cmd_master, cmd_prev, NULL, args);
			get_parenthesis_cmd(args, cmd_master);
		}
		else if (cmd->type == CMD_AND || cmd->type == CMD_OR)
			return (add_previous_cmd(cmd_master, cmd_prev, cmd, args));
		else
			*cmd_prev = cmd;
	}
	return (1);
}
