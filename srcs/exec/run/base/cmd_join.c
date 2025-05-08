/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:34:41 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/08 15:53:17 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_bool	is_redirection(t_node_type type);

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

static char *save_word(t_dynarray *argv, t_dynarray *word)
{
	char	*joined;
	
	joined = contentsjoin(word);
	if (!joined)
		return (NULL);
	set_dynarray_value(argv, argv->count, joined);
	if (!argv->data)
	{
		free(joined);
		return (NULL);
	}
	return (argv->data[argv->count - 1]);
}

static void	skip_redirection(t_uint *i, t_uint count, t_dynarray *arr)
{
	t_ast_node	*node;

	while (*i < count)
	{
		node = (t_ast_node *)get_dynarray_value(arr, *i);
		if (!is_redirection(node->type))
			break ;
		(*i)++;
	}
}

t_dynarray	*cmd_to_argv(t_dynarray *arr, t_dynarray *argv)
{
	t_ast_node	*node;
	t_uint		i;

	if (!argv->data)
		return (NULL);
	i = 0;
	while (i < arr->count)
	{
		skip_redirection(&i, arr->count, arr);
		node = (t_ast_node *)get_dynarray_value(arr, i);
		if (node && !save_word(argv, node->content))
			return (destroy_dynarray(argv));
		i++;
	}
	return (argv);
}


