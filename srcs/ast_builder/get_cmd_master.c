#include "ast.h"

t_dynamic_array	*get_cmd_master(t_get_cmd_master args)
{
	int i;
	int pos;
	t_ast_node *cmd_prev;
	t_ast_node *cmd;
	t_dynamic_array	*cmd_master = init_dynamic_array_malloc(40, NULL);

	i = args.start;
	pos = 0;
	args.local_node_info.cmd_master = cmd_master;
	args.local_node_info.pos = &pos;
	cmd_prev = NULL;
	while (i < args.end)
	{
		cmd = get_cmd(args.tokens, &i, args.end);
		if (i == args.end)
			set_value(cmd_master, pos, cmd);
		else if (cmd->type == CMD_PIPE)
		{
			add_child(cmd, cmd_prev);
			cmd_prev = NULL;
			if (get_pipe_cmd(cmd, args, &i, &cmd_prev) == 1)
			{
				set_value(cmd_master, pos, cmd);
				pos++;
			}
		}
		else if (cmd->type == CMD_AND || cmd->type == CMD_OR)
			get_or_and_cmd_wrapper(cmd, args, &i, &cmd_prev);
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
		{
			get_parenthesis_cmd_master(args, cmd_master, &i, pos);
			pos++;
		}
		else
			cmd_prev = cmd;
	}
	return (cmd_master);
}
