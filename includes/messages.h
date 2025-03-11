#ifndef MESSAGES_H
# define MESSAGES_H

# include <stdio.h>

# define SHELL_NAME "minishell >"

# define ERROR_MALLOC "Error: malloc"

# define ERROR_CD "cd"
# define ERROR_CD_HOME "cd: HOME not set"
# define ERROR_CD_OLDPWD "cd: OLDPWD not set"
# define ERROR_GETCWD \
"cd: error retrieving current directory: getcwd: cannot access parent directories"

# define ERROR_SHELL_INIT \
"shell-init: error retrieving current directory: getcwd: cannot access parent directories"

#endif

