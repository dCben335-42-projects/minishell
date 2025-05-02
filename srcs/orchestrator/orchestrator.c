#include "ast.h"
#include "orchestrator.h"
#include "cmd.h"
#include "cmd_expand.h"
#include "cmd_builtin.h"

void	execute_cmd_base(t_shell *shell, t_dynarray *cmd)
{
	t_dynarray	*args;
	char ***argv;

	args = dynarray_to_argv(cmd);
	argv = (char ***)&args->data;
	expand(shell, args);
	if (!is_builtin(*argv, shell))
	{
		args->data[0] = get_full_cmd_path(*argv, get_env_node(shell->env, "PATH"));
		fork_and_exec(shell, args, *argv);
	}
	destroy_dynarray(args);
	return ;
}

void	execute_cmd_and()
{
	return ;
}

void	execute_cmd_or()
{
	return ;
}

void	execute_cmd_pipe()
{
	return ;
}

void	orchestrator(t_shell *shell)
{
	t_ast_node	*cmd;
	t_ast_node	master_node;

	master_node.type = CMD_SEQ;
	master_node.content = NULL;
	master_node.child_count = 0;
	master_node.parent = NULL;
	master_node.next = NULL;
	add_childs(&master_node, shell->ast);
	cmd = find_next_cmd(&master_node);
	printf("--------------------\n");
	while (cmd)
	{
		print_ast_json_wrapper(cmd->content);
		if (cmd->parent->type == CMD_SEQ)
			execute_cmd_base(shell, cmd->content);
		if (cmd->parent->type == CMD_AND)
			execute_cmd_and();
		if (cmd->parent->type == CMD_OR)
			execute_cmd_or();
		if (cmd->parent->type == CMD_PIPE)
			execute_cmd_pipe();
		cmd = find_next_cmd(&master_node);
	}
}

// ( ( ( echo 'salut' ) ) && echo 'bonjour' ) | echo bar | echo "sa va"