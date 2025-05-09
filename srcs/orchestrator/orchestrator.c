#include "ast.h"
#include "orchestrator.h"
#include "cmd.h"
#include "cmd_expand.h"
#include "cmd_builtin.h"
#include <fcntl.h>
#include <unistd.h>
# include "cmd.h"
#include <fcntl.h>
#include <unistd.h>


void	cleanup_args(t_dynarray *arr)
{
	t_uint	i;
	t_uint	j;
	t_uint	count;
	char	*str;
	
	if (!arr || !arr->data)
		return;
	count = arr->count;
	i = 0;
	j = 0;
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

#include "errors.h"

void exec2(t_shell *shell, t_dynarray *cmd, char **argv)
{
	if (!is_builtin(shell, cmd, argv))
	{
		argv[0] = get_full_cmd_path(argv, get_env_node(shell->env, "PATH"));
		if (!argv[0])
			destroy_child(shell, argv, EXIT_FAILURE);
		fork_and_exec(shell, argv, cmd);
	}
}


void exec(t_shell *shell, t_dynarray *cmd, char **argv)
{
	exec2(shell, cmd, argv);
}		
	
void	execute_cmd_base(t_shell *shell, t_dynarray *cmd)
{
	t_dynarray	args;

	args = init_dynarray(1, free_value);
	if (!cmd_to_argv(cmd, &args) || !expand(shell, &args))
		return ;
	cleanup_args(&args);
	exec(shell, cmd, (char **)args.data);
	destroy_dynarray(&args);
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

typedef struct s_exec_map
{
	t_node_type	type;
	void		(*f)(t_shell *shell, t_dynarray *cmd);
}	t_exec_map;

const t_exec_map	*get_exec_map(void)
{
	static const t_exec_map	map[] = {
	{CMD_SEQ, &execute_cmd_base},
	{CMD_JOIN, &execute_cmd_base},
	{CMD_AND, &execute_cmd_and},
	{CMD_OR, &execute_cmd_or},
	{CMD_PIPE, &execute_cmd_pipe},
	{0, NULL}};

	return (map);
}

void handle_cmd(t_shell *shell, t_ast_node *cmd, const t_node_type type)
{
	const t_exec_map	*exec_map = get_exec_map();

	while (exec_map->type)
	{
		if (exec_map->type == type)
		{
			exec_map->f(shell, cmd->content);
			break ;
		}
		exec_map++;
	}
}

void	handle_subshell(t_shell *shell, t_ast_node *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		shell->exit_code = EXIT_FAILURE;
		return ;
	}
	else if (pid == 0)
	{
		handle_cmd(shell, cmd, cmd->type);
		cmd = find_next_cmd(cmd);
		while (cmd && cmd->parent && cmd->parent->parent && cmd->parent->parent->type == CMD_PARENTHESIS)
		{
			handle_cmd(shell, cmd, cmd->parent->type);
			cmd = find_next_cmd(cmd);
		}
		destroy_child(shell, NULL, shell->exit_code);
	}
	wait_childrens();
}

void	orchestrator(t_shell *shell)
{
	t_ast_node	*cmd;

	cmd = find_next_cmd(shell->ast);
	while (cmd)
	{
		if (cmd->parent->type == CMD_PARENTHESIS)
		{
			handle_subshell(shell, cmd);
			cmd = find_next_cmd(cmd);
			while (cmd && cmd->parent && cmd->parent->parent && cmd->parent->parent->type == CMD_PARENTHESIS)
				cmd = find_next_cmd(cmd);
			continue;
		}
		handle_cmd(shell, cmd, cmd->parent->type);
		cmd = find_next_cmd(cmd);
	}
}

// ( ( ( echo 'salut' ) ) && echo 'bonjour' ) | echo bar | echo "sa va"