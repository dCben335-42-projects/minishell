#include "ast.h"

int	get_pipe_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev)
{
	t_ast_node *cmd;
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
		print_cmd_type(cmd->type);
		if (*i == args.end)
			return (add_child(cmd_master, cmd));
		else if (cmd->type == CMD_PIPE)
		{
			add_child_secure(cmd_master, cmd_prev);
			free(cmd);
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
			get_parenthesis_cmd(args, cmd_master, i);
		else if (cmd->type != CMD)
			return (add_previous_cmd(cmd_master, cmd_prev, i, cmd));
		else
			*cmd_prev = cmd;
	}
	return (1);
}
