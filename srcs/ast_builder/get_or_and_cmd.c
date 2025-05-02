#include "ast.h"

static void	get_or_and_cmd_next_parenthesis(t_ast_node **cmd_prev, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	add_child_secure(cmd_master, cmd_prev, args);	// ajoute le texte (cmd_prev) au cmd_master (&& ||)
	get_parenthesis_cmd(args, cmd_master);
}

static void	get_or_and_cmd(t_ast_node **cmd_prev, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	t_bool		is_empty;

	while (args->i < args->end)
	{
		args->local.ctx = CTX_AND_OR;
		if (!get_cmd(args, &is_empty))
			continue ;
		if (args->local.cmd == NULL)
			return ;
		if (args->i == args->end)
			return (add_child_secure(cmd_master, &args->local.cmd, args));
		if (is_cmd(args, CMD_PIPE))
			get_pipe_cmd_wrapper(cmd_prev, cmd_master, args);
		else if (is_cmd(args, CMD_PARENTHESIS_OPEN))
			get_or_and_cmd_next_parenthesis(cmd_prev, cmd_master, args);
		else if (is_cmd(args, CMD_AND | CMD_OR))
			return (add_child_secure(cmd_master, cmd_prev, args));
		else
			*cmd_prev = args->local.cmd;
	}
}

void	get_or_and_cmd_wrapper(t_ast_node **cmd_prev, t_ast_node *cmd_master, t_get_cmd_master *args)
{
	t_ast_node	*cmd;

	cmd = args->local.cmd;
	args->local.cmd = &args->local.lcmd;
	add_child_secure(cmd_master, cmd_prev, args);
	if (is_node(cmd, CMD_PARENTHESIS_OPEN))
		get_parenthesis_cmd_master(cmd_master, args);
	else
	{
		get_or_and_cmd(cmd_prev, cmd, args);
		add_child_secure(cmd_master, &cmd, args);
	}
}
