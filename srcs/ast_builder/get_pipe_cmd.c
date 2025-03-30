#include "ast.h"

int	get_pipe_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev)
{
	t_ast_node *cmd;

	while (*i < args.end)
	{
		cmd = get_cmd(args.tokens, i, args.end);
		if (*i == args.end)
			return (add_child(cmd_master, cmd));
		else if (cmd->type == CMD_PIPE)
		{
			if (*cmd_prev)
				add_child(cmd_master, *cmd_prev);
			*cmd_prev = NULL;
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
			get_parenthesis_cmd(args, cmd_master, i);
		else if (cmd->type != CMD)
			return (add_previous_cmd(cmd, cmd_prev, i, TRUE));
		else
			*cmd_prev = cmd;
	}
	return (1);
}
