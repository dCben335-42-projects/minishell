#include "ast.h"

int	get_pipe_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev)
{
	t_ast_node *cmd;

	while (*i < args.end)
	{
		cmd = get_cmd(args.tokens, i, args.end);
		if (*i == args.end)
		{
			add_child(cmd_master, cmd);
			return (1);
		}
		else if (cmd->type == CMD_PIPE)
		{
			add_child(cmd_master, *cmd_prev);
		}
		else if (cmd->type != CMD)
		{
			(*i)--;
			add_child(cmd_master, *cmd_prev);
			*cmd_prev = NULL;
			return (1);
		}
		else if (cmd->type == CMD)
		{
			*cmd_prev = cmd;
		}
	}
	return (1);
}