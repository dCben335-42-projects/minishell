/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:01:55 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/07 18:34:00 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "ast_node.h"
#include <fcntl.h>
#include <unistd.h>
#include "errors.h"
#include "cmd_expand.h"

void restore_std_in_out(int saved_stdin, int saved_stdout);

typedef struct s_redir_map
{
	t_node_type	type;
	int			flags;
	int 		mode;
}	t_redir_map;

static const t_redir_map *get_redir_map(void)
{
	static const t_redir_map redir_map[] = {
		{CMD_REDIR_OUT, O_WRONLY | O_CREAT | O_TRUNC, 0644},
		{CMD_APPEND, O_WRONLY | O_CREAT | O_APPEND, 0644},
		{CMD_REDIR_IN, O_RDONLY, 0},
		{CMD_HEREDOC, O_RDONLY | O_CREAT | O_APPEND, 0644},
		{0, 0, 0}
	};

	return (redir_map);
}

static int  open_redirection(t_node_type type, const char *filename)
{
	const t_redir_map	*redir_map = get_redir_map();

	if (!filename)
		return (-1);
	while (redir_map->type)
	{
		if (redir_map->type == type)
			return (open(filename, redir_map->flags, redir_map->mode));
		redir_map++;
	}
	return (-1);
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

static char *contentsjoin(t_dynarray *word)
{
	t_ast_node	*node;
	char	*join;
	char	*tmp;
	t_uint	i;

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

char **expand_filename(t_shell *shell, char *filename)
{
	char *expanded_filename;
	char **splited_filename;

	if (!filename)
		return (NULL);
	expanded_filename = ft_strdup(filename);
	if (!expanded_filename)
		return (NULL);
	expand_env_token(shell, &expanded_filename);
	if (!expanded_filename)
		return (NULL);
	expand_wildcard_token(shell, &expanded_filename);
	if (!expanded_filename)
		return (NULL);
	splited_filename = ft_split(expanded_filename, ' ');
	free(expanded_filename);
	return (splited_filename);
}

t_bool	is_valid_filename(char **expanded_filename)
{
	if (!expanded_filename || !*expanded_filename || !**expanded_filename)
		return (FALSE);
	if (expanded_filename[1])
		return (FALSE);
	return (TRUE);
}

t_bool	handle_redirections(t_shell *shell, t_dynarray *cmd)
{
	t_ast_node	*node;
	char		*filename;
	char 		**expanded_filename;
	int			fd;
	t_uint		i = 0;


	while (i < cmd->count)
	{
		skip_words(cmd, &i);
		node = (t_ast_node *)cmd->data[i];
		if (node)
		{
			filename = contentsjoin(node->content);
			if (!filename)
				return (FALSE);
			expanded_filename = expand_filename(shell, filename);
			if (!expanded_filename)
			{
				free(filename);
				return (FALSE);
			}
			if (!is_valid_filename(expanded_filename))
			{
				ft_putstr_fd(filename, 2);
				ft_putstr_fd(": ambiguous redirect\n", 2);
				free(filename);
				ft_free_split(expanded_filename);
				return (FALSE);
			}
			fd = open_redirection(node->type, *expanded_filename);
			if (!p_int(fd, -1, filename))
			{
				free(filename);
				ft_free_split(expanded_filename);
				return (FALSE);
			}
			if (node->type == CMD_REDIR_IN)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
			free(filename);
			ft_free_split(expanded_filename);
		}
		i++;
	}
	return (TRUE);
}
