#include "orchestrator.h"
#include "cmd.h"

static void	cleanup_args(t_dynarray *arr)
{
	t_uint	i;
	t_uint	j;
	t_uint	count;
	char	*str;
	
	if (!arr || !arr->data)
		return;
	i = 0;
	j = 0;
	count = arr->count;
	while (i < count)
	{
		str = get_dynarray_value(arr, i);
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

static char *save_word(t_shell *shell, t_dynarray *argv, t_dynarray *word)
{
	char	*expanded_word;

	expanded_word = expand_word(shell, word);
	if (!expanded_word || !set_dynarray_value(argv, argv->count, expanded_word))
	{
		free(expanded_word);
		return (NULL);	
	}
	return (expanded_word);
}

static void	skip_redirection(t_uint *i, t_uint count, t_dynarray *arr)
{
	t_ast_node	*node;

	while (*i < count)
	{
		node = (t_ast_node *)get_dynarray_value(arr, *i);
		if (node->type == CMD_WORD)
			break ;
		(*i)++;
	}
}

static t_dynarray	*cmd_to_argv(t_shell *shell, t_dynarray *arr, t_dynarray *argv)
{
	t_ast_node	*node;
	t_uint		i;

	if (!argv->data)
		return (NULL);
	i = 0;
	while (i < arr->count)
	{
		skip_redirection(&i, arr->count, arr);
		node = (t_ast_node *)get_dynarray_value(arr, i);
		if (node && !save_word(shell, argv, node->content))
			return (destroy_dynarray(argv));
		i++;
	}
	return (argv);
}

/**
 * @brief Executes a basic command in the shell.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @return The next command node to execute or NULL if there are no more commands.
 */
t_ast_node	*exec_basic(t_shell *shell, t_ast_node *cmd)
{
	t_dynarray	args;
	char		***argv;

	args = init_dynarray(1, free_value);
	if (!cmd_to_argv(shell, cmd->content, &args))
		return (NULL);
	cleanup_args(&args);
	argv = (char ***)&args.data;
	if (!is_builtin(shell, cmd->content, *argv))
	{
		*argv[0] = get_full_cmd_path(*argv, get_env_node(shell->env, "PATH"));
		if (!*argv[0])
			destroy_self(shell, *argv, EXIT_FAILURE);
		fork_and_exec(shell, *argv, cmd->content);
	}
	destroy_dynarray(&args);
	return (find_next_cmd(cmd));
}
