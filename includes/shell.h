#ifndef SHELL_H
# define SHELL_H

# include "env.h"

typedef struct s_shell {
    t_env	*env;
	char	*home;
} t_shell;

#endif