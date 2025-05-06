#include "ast.h"
#include "orchestrator.h"
#include "cmd.h"
#include "cmd_expand.h"
#include "cmd_builtin.h"
#include <fcntl.h>
#include <unistd.h>

void	cleanup_args(t_dynarray *arr)
{
	t_uint	i;
	t_uint	j;
	t_uint	count;
	char	*str;
	
	count = arr->count;
	i = 0;
	j = 0;
	if (!arr || !arr->data)
		return;
	while (i < count)
	{
		str = (char *)arr->data[i];
		if (str && *str)
			arr->data[j++] = arr->data[i];
		else if (arr->destroyer)
			arr->destroyer(arr->data[i]); 
		i++;
	}
	arr->count = j;
	while (j < count)
		arr->data[j++] = NULL;
}


void	execute_cmd_base(t_shell *shell, t_dynarray *cmd)
{
	t_dynarray	*args;
	char		***argv;

	args = dynarray_to_argv(cmd);
	if (!args)
		return ;
	argv = (char ***)&args->data;
	expand(shell, args);
	cleanup_args(args);
	if (!is_builtin(*argv, shell, cmd))
	{
		args->data[0] = get_full_cmd_path(*argv, get_env_node(shell->env, "PATH"));
		fork_and_exec(shell, args, *argv, cmd);
	}
	destroy_dynarray(args);
}

void	execute_cmd_and(t_shell *shell, t_dynarray *cmd)
{
	if (!shell->exit_code)
		execute_cmd_base(shell, cmd);
}

void	execute_cmd_or(t_shell *shell, t_dynarray *cmd)
{
	if (shell->exit_code)
		execute_cmd_base(shell, cmd);
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
			execute_cmd_and(shell, cmd->content);
		if (cmd->parent->type == CMD_OR)
			execute_cmd_or(shell, cmd->content);
		// if (cmd->parent->type == CMD_PIPE)
		// 	execute_cmd_pipe();
		cmd = find_next_cmd(&master_node);
	}
}

// ( ( ( echo 'salut' ) ) && echo 'bonjour' ) | echo bar | echo "sa va"