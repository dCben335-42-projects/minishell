#include "ast.h"

t_dynamic_array	*get_cmd_master(t_get_cmd_master args)
{
	int i;
	int pos;
	t_ast_node *cmd_prev;
	t_ast_node *cmd;
	t_dynamic_array	*cmd_master = init_dynamic_array_malloc(40, NULL);
	(void)args.end;

	i = args.start;
	pos = 0;
	cmd_prev = NULL;
	while (i < args.end)
	{
		cmd = get_cmd(args.tokens, &i, args.end);
		print_cmd_type(cmd->type);
		if (i == args.end)
		{
			set_value(cmd_master, pos, cmd);
		}
		else if (cmd->type == CMD_PIPE)
		{
			add_child(cmd, cmd_prev);
			if (get_pipe_cmd(cmd, args, &i, &cmd_prev) == 1)
			{
				set_value(cmd_master, pos, cmd);
				pos++;
			}
		}
		else if (cmd->type == CMD_AND)
		{
			if (pos == 0)
			{
				set_value(cmd_master, pos, cmd_prev);
				pos++;
			}
			if (get_or_and_cmd(cmd, args, &i, &cmd_prev))
			{
				set_value(cmd_master, pos, cmd);
				pos++;
			}
		}
		else if (cmd->type == CMD_OR)
		{
			if (pos == 0)
			{
				set_value(cmd_master, pos, cmd_prev);
				pos++;
			}
			print_ast_json_wrapper(cmd_master);
			if (get_or_and_cmd(cmd, args, &i, &cmd_prev))
			{
				set_value(cmd_master, pos, cmd);
				pos++;
			}
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
		{
			get_parenthesis_cmd_master(args, cmd_master, &i, pos);
			pos++;
		}
		else
		{
			cmd_prev = cmd;
		}
		//print_ast_json_wrapper(cmd_master);
	}

	return (cmd_master);
}