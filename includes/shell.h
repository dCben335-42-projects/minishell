#ifndef SHELL_H
# define SHELL_H

# include "env.h"

typedef struct s_shell
{
    t_env	*env;
	char	*current_path;
} t_shell;

t_shell	init_shell(char **envp);
void	*destroy_shell(t_shell *shell);

#endif