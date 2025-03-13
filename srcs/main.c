#include "messages.h"
#include "minishell.h"
#include "libft.h"
#include "builtin.h"

void	execute_command(char **args)
{
    if (fork() == 0) 
	{ 
		execvp(args[0], args);
		exit(1); 
	}
    wait(NULL);
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
				execute_command(args);
		ft_handle_free_split(args);
		free(input);
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

