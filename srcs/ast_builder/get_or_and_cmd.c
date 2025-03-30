#include "ast.h"

int	get_or_and_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev)
{
	t_ast_node *cmd;

	while (*i < args.end)
	{
		cmd = get_cmd(args.tokens, i, args.end);
		print_cmd_type(cmd->type);
		if (*i == args.end)
		{
			add_child(cmd_master, cmd);
			return (1);
		}
		if (cmd->type == CMD_PIPE)
		{
			add_child(cmd, *cmd_prev);
			if (get_pipe_cmd(cmd, args, i, cmd_prev) == 1)
			{
				add_child(cmd_master, cmd);
			}
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
			get_parenthesis_cmd(args, cmd_master, i);
		else if (cmd->type == CMD_AND)
		{
			(*i)--; // on revient en arrière pour traiter le AND
			if (*cmd_prev)
				add_child(cmd_master, *cmd_prev);
			return (1);
		}
		else if (cmd->type == CMD_OR)
		{
			(*i)--; // on revient en arrière pour traiter le OR
			if (*cmd_prev)
				add_child(cmd_master, *cmd_prev);
			return (1);
		}
		else
		{
			*cmd_prev = cmd;
		}
	}
	return (1);
}