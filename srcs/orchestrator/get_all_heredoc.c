#include "ast.h"
#include "minishell.h"
#include "fcntl.h"

static void	put_in_pipe(t_ast_node *cmd_heredoc)
{
	int *pipefd = malloc(sizeof(int) * 2);

	pipe(pipefd);
	while (1) {
		char *line = readline(SHELL_NEXT_NAME);
		if (!line)
			break;
		if (strcmp(line, cmd_heredoc->content) == 0) {
			free(line);
			break;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	free(cmd_heredoc->content);
	cmd_heredoc->content = (void *)pipefd;
}
	

static char *contentsjoin(t_dynarray *word)
{
    t_ast_node    *node;
    char    *join;
    char    *tmp;
    t_uint    i;

    join = ft_strdup("");
    if (!join)
        return (NULL);
    i = 0;
    while (i < word->count)
    {
        node = (t_ast_node *)get_dynarray_value(word, i);
        tmp = ft_strjoin(join, (char *)node->content);
        if (!tmp)
        {
            free(join);
            return (NULL);
        }
        free(join);
        join = tmp;
        i++;
    }
    return (join);
}

//void	reassemble_word(t_ast_node *cmds)
//{

//	printf("--------------------\n");
//	print_ast_json_wrapper(cmds->content);
//	if (cmd->parent->type == CMD_HEREDOC)
//	{
//		printf("HEREDOC\n");
//		put_in_pipe(contentsjoin(cmd->parent->content), cmd->parent);
//	}
//	else
//	{
//		tmp = cmd->parent->content;
//		cmd->parent->content = contentsjoin(tmp);
//		free(tmp);
//	}
//}

static char *save_word(t_ast_node *node)
{
	char	*joined;
	
	joined = contentsjoin(node->content);
	if (!joined)
		return (NULL);
	destroy_dynarray(node->content);
	node->content = (void *)joined;
	node->child_count = 1;
	return (node->content);
}

t_dynarray	*dynarray_to_argv(t_dynarray *cmd)
{
	t_ast_node	*node;
	t_uint		i;

	i = 0;
	while (i < cmd->count)
	{
		node = (t_ast_node *)get_dynarray_value(cmd, i);
		if (!save_word(node))
			return (NULL);
		if (node->type == CMD_HEREDOC)
			put_in_pipe(node);
		i++;
	}
	return (cmd);
}

void	get_all_heredoc(t_ast_node *cmds)
{
	t_ast_node	*cmd;

	cmd = find_next_cmd(cmds);
	while (cmd)
	{
		printf("cmd type: %d\n", cmd->type);
		if (!dynarray_to_argv(cmd->content))
			return ;
		cmd = find_next_cmd(cmds);
	}
}
