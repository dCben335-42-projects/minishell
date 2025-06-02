#include "ast.h"

static void	add_cmd_master(t_ast_node **cmd_prev, t_get_cmd_master *args)
{
	if (is_cmd(args, CMD_SEMICOL))
		add_child(args->local.cmd_master, cmd_prev, args);
	else if (args->i == args->end)
		add_child(args->local.cmd_master, &args->local.cmd, args);
	else if (is_cmd(args, CMD_PIPE))
		get_pipe_cmd_wrapper(cmd_prev, args->local.cmd_master, args);
	else if (is_cmd(args, CMD_AND | CMD_OR | CMD_PARENTHESIS_OPEN))
		other_op_handler(cmd_prev, args->local.cmd_master, args);
	else
		*cmd_prev = args->local.cmd;
}

/**
 * 
 * @brief Extracts commands from tokens and adds them to the master node.
 * 
 * @param args Structure with tokens, indices, and the master command node.
 * 
 * @note The master node can be a cmd_seq or cmd_parenthesis.
 * 
*/
void	get_cmd_master(t_get_cmd_master *args)
{
	t_ast_node		*cmd_prev;
	
	cmd_prev = NULL;
	while (args->i < args->end)
	{
		if (args->has_malloc_error)
			return ;
		args->local.ctx = CTX_MASTER;
		if (!get_cmd(args))
			continue ;
		add_cmd_master(&cmd_prev, args);
	}
	return ;
}
