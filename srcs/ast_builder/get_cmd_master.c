#include "ast.h"

t_dynamic_array	*get_cmd_master(t_get_cmd_master args)
{
	int i;
	int pos;
	t_ast_node *cmd_prev;
	t_ast_node *cmd;
	t_dynamic_array	*cmd_master = init_dynamic_array_malloc(80, (void *(*)(void *))recursive_destroy_node); // 1
	t_bool is_empty;

	i = args.start;
	pos = 0;
	args.local_node_info.cmd_master = cmd_master;
	args.local_node_info.pos = &pos;
	cmd_prev = NULL;
	while (i < args.end)
	{
		if (*(args.has_malloc_error) == TRUE)
		{
			printf("bool: %d", *(args.has_malloc_error));
			printf("i=%d", i);
			printf("malloc error\n");
			return (cmd_master);
		}
		cmd = get_cmd(args, &i, &is_empty);
		if (is_empty)
		{
			is_empty = FALSE;
			continue ;
		}
		if (cmd == NULL)
			return (NULL);
		if (i == args.end)
			set_dynarray_value_secure(cmd_master, pos, cmd, args);
		else if (cmd->type == CMD_PIPE)
		{
			add_child_secure(cmd, &cmd_prev, args);
			if (get_pipe_cmd(cmd, args, &i, &cmd_prev) == 1)
			{
				set_dynarray_value_secure(cmd_master, pos, cmd, args);
				pos++;
			}
		}
		else if (cmd->type == CMD_AND || cmd->type == CMD_OR)
		{
			if (cmd_prev)
			{
				set_dynarray_value_secure(cmd_master, pos, cmd_prev, args);
				cmd_prev = NULL;
				pos++;
			}
			get_or_and_cmd_wrapper(cmd, args, &i, &cmd_prev);
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
		{
			free(cmd);
			if (cmd_prev)
			{
				set_dynarray_value_secure(cmd_master, pos, cmd_prev, args);
				cmd_prev = NULL;
				pos++;
			}
			get_parenthesis_cmd_master(args, cmd_master, &i, pos);
			pos++;
		}
		else
			cmd_prev = cmd;
	}
	return (cmd_master);
}
