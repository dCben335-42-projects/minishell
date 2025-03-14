#include "messages.h"
#include "minishell.h"
#include "libft.h"
#include "builtin.h"

void	execute_command(char *path, char **args)
{
    if (fork() == 0) 
	{ 
		execvp(path, args);
		exit(1); 
	}
    wait(NULL);
}

void	handle_command(t_shell *shell, char **args)
{
	const t_env	*node = get_env_node(shell->env, PATH_KEY);
	if (node)
	{
		char	**paths;
		char	*path;
		size_t	i;

		paths = ft_split(node->value, ':');
		i = 0;
		while (paths[i])
		{
			path = ft_strjoin(paths[i], "/");
			path = ft_strjoin(path, args[0]);
			if (!access(path, F_OK))
			{
				execute_command(path, args);
				break ;
			}
			free(path);
			i++;
		}
		ft_handle_free_split(paths);
		return ;
	}
	ft_putendl_fd("minishell: command not found: ", STDERR_FILENO);
}


static void handle_loop(t_shell *shell)
{
	char		*input;
	char		**args;

	while (TRUE)
	{
		input = readline(SHELL_NAME);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		args = ft_split(input, ' ');
		if (args[0])
			if (!is_builtin(args, shell))
				handle_command(shell, args);
		ft_handle_free_split(args);
		free(input);
		printf("exit code: %d\n", shell->exit_code);
	}
}

int main(int argc, char **argv, char **envp)
{
	const char	*exit_args[] = { "exit", NULL };    
	t_shell		shell;
	
	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	init_signals();
	handle_loop(&shell);
	ft_exit(&shell, (char **)exit_args);
    return (0);
}
