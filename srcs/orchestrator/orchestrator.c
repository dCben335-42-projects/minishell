#include "ast.h"
#include "orchestrator.h"
#include "cmd.h"
#include "cmd_expand.h"
#include "cmd_builtin.h"


#include <fcntl.h>
#include <unistd.h>

t_bool	is_redirection(t_node_type type)
{
	return (
		type == CMD_REDIR_OUT
		|| type == CMD_APPEND
		|| type == CMD_REDIR_IN
		|| type == CMD_HEREDOC
	);
}

t_bool	handle_redirections(t_dynarray *cmd)
{
	t_ast_node	*node;
	t_ast_node	*target;
	int			fd;
	t_uint		i = 0;

	while (i < cmd->count)
	{
		node = (t_ast_node *)cmd->data[i];

		if (is_redirection(node->type))
		{
			t_uint j = i + 1;
			while (j < cmd->count && ((t_ast_node *)cmd->data[j])->type == CMD_SPACE)
				j++;
			if (j >= cmd->count || ((t_ast_node *)cmd->data[j])->type != CMD_TEXT)
				return (FALSE);

			target = (t_ast_node *)cmd->data[j];
			if (node->type == CMD_REDIR_OUT)
				fd = open(target->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (node->type == CMD_APPEND)
				fd = open(target->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (node->type == CMD_REDIR_IN)
				fd = open(target->content, O_RDONLY);
			else
				fd = -1;

			if (fd < 0)
			{
				perror(target->content);
				return (FALSE);
			}
			if (node->type == CMD_REDIR_IN)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		i++;
	}
	return (TRUE);
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
	if (!is_builtin(*argv, shell, cmd))
	{
		args->data[0] = get_full_cmd_path(*argv, get_env_node(shell->env, "PATH"));
		fork_and_exec(shell, args, *argv);
	}
	destroy_dynarray(args);
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