#include "ast.h"

void	get_or_and_cmd_wrapper(t_ast_node *cmd,
	t_get_cmd_master args, int *i, t_ast_node **cmd_prev)
{
	if (get_or_and_cmd(cmd, args, i, cmd_prev))
	{
		set_value(
			args.local_node_info.cmd_master,
			*args.local_node_info.pos,
			cmd
			);
		(*args.local_node_info.pos)++;
	}
}

int	get_or_and_cmd(t_ast_node *cmd_master,
	t_get_cmd_master args, int *i, t_ast_node **cmd_prev)
{
	t_ast_node	*cmd;
	t_bool		is_empty;

	while (*i < args.end)
	{
		cmd = get_cmd(args.tokens, i, args.end, &is_empty);
		if (is_empty)
		{
			is_empty = FALSE;
			continue ;
		}
		if (cmd == NULL)
			return (1);
		if (*i == args.end)
			return (add_child(cmd_master, cmd));
		if (cmd->type == CMD_PIPE)
		{
			add_previous_cmd(cmd, cmd_prev, i, NULL);
			if (get_pipe_cmd(cmd, args, i, cmd_prev) == 1)
				add_child(cmd_master, cmd);
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
		{
			free(cmd);
			add_previous_cmd(cmd_master, cmd_prev, i, NULL);
			get_parenthesis_cmd(args, cmd_master, i);
		}
		else if (cmd->type == CMD_AND || cmd->type == CMD_OR)
			return (add_previous_cmd(cmd_master, cmd_prev, i, cmd));
		else
			*cmd_prev = cmd;
	}
	return (1);
}
