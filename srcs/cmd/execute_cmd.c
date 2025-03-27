#include "messages.h"
#include "minishell.h"
#include "libft.h"
#include "builtin.h"
#include "errors.h"
#include "dynarray.h"
#include "cmd.h"

t_bool	execute_cmd(char *path, char **args)
{
    if (fork() == 0) 
	{ 
		execve(path, args, NULL);
		free(path);
		exit(1); 
	}
    waitpid(-1, NULL, 0);
	free(path);
	return (TRUE);
}
