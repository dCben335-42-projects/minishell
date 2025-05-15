/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:01:55 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/15 20:43:49 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "errors.h"
#include "utils.h"
#include <fcntl.h>

typedef struct s_redir_map
{
	t_node_type	type;
	int			flags;
	int 		mode;
	int 		duped_fd;
}	t_redir_map;

static const t_redir_map *get_redir_map(void)
{
	static const t_redir_map	redir_map[] = {
		{CMD_REDIR_OUT, O_WRONLY | O_CREAT | O_TRUNC, 0644, STDOUT_FILENO},
		{CMD_APPEND, O_WRONLY | O_CREAT | O_APPEND, 0644, STDOUT_FILENO},
		{CMD_REDIR_IN, O_RDONLY, 0, STDIN_FILENO},
		{CMD_HEREDOC, O_RDONLY | O_CREAT | O_APPEND, 0644, STDIN_FILENO},
		{0, 0, 0, -1}
	};

	return (redir_map);
}

static t_bool	open_redirection(t_node_type type, const char *filename)
{
	const t_redir_map	*redir_map = get_redir_map();
	int fd;

	if (!filename)
		return (FALSE);
	while (redir_map->type)
	{
		if (redir_map->type == type)
		{
			fd = open(filename, redir_map->flags, redir_map->mode);
			if (!p_int(fd, -1, filename))
				return (FALSE);
			dup2(fd, redir_map->duped_fd);
			close(fd);
			return (fd);
		}
		redir_map++;
	}
	return (FALSE);
}

t_bool	is_redirection(t_node_type type)
{
	const t_redir_map	*redir_map = get_redir_map();

	while (redir_map->type)
	{
		if (redir_map->type == type)
			return (TRUE);
		redir_map++;
	}
	return (FALSE);
}

static void skip_words(t_dynarray *cmd, t_uint *i)
{
	t_ast_node	*node;

	while (*i < cmd->count)
	{
		node = (t_ast_node *)cmd->data[*i];
		if (node->type != CMD_WORD)
			break ;
		(*i)++;
	}
}

static t_bool	is_valid_filename(char *filename, char *joined_word)
{
	char **splited;

	splited = ft_split(filename, ' ');
	if (!splited)
	{
		free(joined_word);
		return (FALSE);
	}
	if (!*splited || !**splited || splited[1])
	{
		if (!joined_word)
			return (FALSE);
		ft_putstr_fd(joined_word, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		free(joined_word);
		ft_free_split(splited);
		return (FALSE);
	}
	free(joined_word);
	ft_free_split(splited);
	return (TRUE);
}

/**
 * @brief Handles the redirections in the command.
 * 
 * @param shell The shell structure containing the current state.
 * @param cmd The command node to execute.
 * 
 * @note If the redirections are invalid, you should stop the execution of 
 * the current command.
 * 
 * @return TRUE if the redirections were handled successfully, FALSE otherwise.
 */
t_bool	handle_redirections(t_shell *shell, t_dynarray *cmd)
{
	t_ast_node	*node;
	char		*filename;
	char		*joined_word;
	t_uint		i;

	i = 0;
	while (i < cmd->count)
	{
		skip_words(cmd, &i);
		node = (t_ast_node *)cmd->data[i];
		if (node)
		{
			joined_word = word_join(node->content);
			filename = expand_word(shell, node->content);
			if (!filename)
				return ((t_bool) ft_free((void **)&joined_word));
			if (!is_valid_filename(filename, joined_word)
				|| !open_redirection(node->type, filename))
				return ((t_bool) ((void **)&filename));
			free(filename);
		}
		i++;
	}
	return (TRUE);
}
