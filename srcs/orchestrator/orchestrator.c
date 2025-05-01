#include "ast.h"
#include "orchestrator.h"
# include "cmd.h"

void	execute_cmd_base(t_shell *shell, t_dynarray *cmd)
{
	t_dynarray	*argv;
	char ***av;

	argv = dynarray_to_argv(cmd);
	av = (char ***)&argv->data;
	argv->data[0] = get_full_cmd_path(*av, get_env_node(shell->env, "PATH"));
	if (fork() == 0)
	{
		if (!is_valid_cmd_path(*av[0], &shell->exit_code))
		{
			destroy_dynarray(argv);
			destroy_shell(shell);
			exit(EXIT_FAILURE);
		}
		exec_cmd(*av, shell);
	}
	shell->exit_code = wait_childrens();
	destroy_dynarray(argv);
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
	t_ast_node	*master_node;
	t_ast_node	*cmd;

	master_node = init_node(CMD_SEQ, NULL);
	add_childs(master_node, shell->ast);
	cmd = find_next_cmd(master_node);
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
		cmd = find_next_cmd(master_node);
	}
}

// ( ( ( echo 'salut' ) ) && echo 'bonjour' ) | echo bar | echo "sa va"