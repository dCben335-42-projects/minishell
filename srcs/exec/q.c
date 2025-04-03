#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft.h"

t_bool	is_valid_cmd_path(char *path, int *exit_code);
char	*get_full_cmd_path(char **cmd, char *paths);

typedef struct s_pipex
{
    int		fd[2];
    int		tmp_fd;    
    char	**cmds;
    int		cmd_count;
	int		exec_count;
    int		exit_code;
	char	*paths;
}   t_pipex;


t_pipex	init_pipex(char *input)
{
	t_pipex pipex;

    pipex.tmp_fd = -1;
    pipex.cmds = ft_split(input, '|');
    pipex.cmd_count = ft_split_len(pipex.cmds);
	pipex.exit_code = 0;
	pipex.exec_count = 0;
	pipex.paths = getenv("PATH");
	return (pipex);
}

void	*destroy_pipex(t_pipex *pipex)
{
	ft_free_split(pipex->cmds);
	return (NULL);
}


void	exec_cmd(char **argv, t_pipex *pipex)
{
	execve(argv[0], argv, NULL);
	perror("execve");
	ft_free_split(argv);
	destroy_pipex(pipex);
	exit(EXIT_FAILURE);
}

void	wait_child(int *exit_code)
{
	int		status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			*exit_code = WEXITSTATUS(status);
			printf("EXIT exit code: %d\n", *exit_code);
		}
		else if (WIFSIGNALED(status))
		{
			*exit_code = 128 + WTERMSIG(status);
			printf("SIGN exit code: %d\n", *exit_code);
		}
		else if (WIFSTOPPED(status))
		{
			*exit_code = 128 + WSTOPSIG(status);
			printf("STOP exit code: %d\n", *exit_code);
		}
		else
			*exit_code = 1;
	}
}


// void handle_pipe_forked(t_pipex *pipex, int i, char **argv)
// {
//     int code;

// 	dup2(pipex->prev_fd, STDIN_FILENO);
// 	dup2(pipex->fd[1], STDOUT_FILENO); 
//     close(pipex->fd[0]);
//     close(pipex->fd[1]);
//     close(pipex->prev_fd);
//     if (!is_valid_cmd_path(argv[0], &code))
//     {
//         ft_handle_free_split(argv);
//         destroy_pipex(pipex);
//         exit(code);
//     }
//     exec_cmd(argv, pipex);
// }

// void pipeline(t_pipex *pipex)
// {
//     int i = 0;
//     char **cmd;

//     while (i < pipex->cmd_count)
//     {
//         cmd = ft_split(pipex->cmds[i], ' ');
//         cmd[0] = get_full_cmd_path(cmd, pipex->paths);
//         if (cmd[0]) 
//         {
//             if (i < pipex->cmd_count - 1)
//                 pipe(pipex->fd);
//             if (fork() == 0)
//                 handle_pipe_forked(pipex, i, cmd);
//             if (i > 0)
//                 close(pipex->prev_fd);
// 			if (i > 0 && i < pipex->cmd_count - 1)
// 				close(pipex->fd[1]);
// 			if (i < pipex->cmd_count - 1)
//            		pipex->prev_fd = pipex->fd[0];
//         }
//         ft_handle_free_split(cmd);
//         i++;
//     }
//     close(pipex->prev_fd);
//     wait_child(&pipex->exit_code);
// }


void execute_pipex(t_pipex *pipex)
{
	char **cmd;

	pipex->tmp_fd = STDIN_FILENO;
    for (int i = 0; i < pipex->cmd_count; i++)
    {
		if (i < pipex->cmd_count - 1)
			pipe(pipex->fd);
        if (fork() == 0)
        {
            if (i > 0)
                dup2(pipex->tmp_fd, STDIN_FILENO);
            if (i < pipex->cmd_count - 1)
                dup2(pipex->fd[1], STDOUT_FILENO);
            close(pipex->fd[0]);
            close(pipex->fd[1]);

            cmd = ft_split(pipex->cmds[i], ' ');
			cmd[0] = get_full_cmd_path(cmd, pipex->paths);
			if (!is_valid_cmd_path(cmd[0], &pipex->exit_code))
			{
				ft_free_split(cmd);
				destroy_pipex(pipex);
				exit(pipex->exit_code);
			}
            execvp(cmd[0], cmd);
			perror("execvp");
			ft_free_split(cmd);
			destroy_pipex(pipex);
			exit(EXIT_FAILURE);
        }
		close(pipex->fd[1]);
		pipex->tmp_fd = pipex->fd[0];
		if (i > 0)
			close(pipex->tmp_fd);
    }
    wait_child(&pipex->exit_code);
	close(pipex->tmp_fd);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}


int main(int argc, char *argv[])
{
    t_pipex pipex;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s \"commande1 | commande2 | ...\"\n", argv[0]);
        return (1);
    }
    pipex = init_pipex(argv[1]);
    // pipeline(&pipex);
	execute_pipex(&pipex);
	printf("exit code: %d\n", pipex.exit_code);
	destroy_pipex(&pipex);
    return (0);
}
