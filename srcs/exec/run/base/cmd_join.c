/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:34:41 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/07 15:32:54 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char *save_string(t_dynarray *new, char **str)
{
	if (!set_dynarray_value(new, new->count, *str))
	{
		free(*str);
		*str = NULL;
		return (NULL);
	}
	*str = NULL;
	return (new->data[new->count - 1]);
}

static char *get_current_string(t_ast_node *node, char *str)
{
	char		*to_add;
	char 		*tmp;

	if (node->content )
		to_add = node->content;
	else
		to_add = "";
	if (!str)
		str = ft_strdup(to_add);
	else
	{
		tmp = ft_strjoin(str, to_add);
		free(str);
		if (!tmp)
			return (NULL);
		str = tmp;
	}
	return (str);
}

t_bool	is_redirection(t_node_type type);


t_dynarray	*dynarray_to_argv(t_dynarray *arr)
{
	t_dynarray	*argv;
	t_uint		i;
	char		*current;
	t_ast_node	*node;


	current = NULL;
	argv = init_dynarray_malloc(1, free_value);
	if (!argv)
		return (NULL);
	i = 0;
	while (i < arr->count)
	{
		node = (t_ast_node *)get_dynarray_value(arr, i);
		if (is_redirection(node->type))
			break ;
		if (node->type == CMD_SPACE)
		{
			if (!save_string(argv, &current))
				return (destroy_dynarray(argv));
		}
		else
		{
			current = get_current_string(node, current);
			if (!current)
				return (destroy_dynarray(argv));
		}
		i++;
	}
	if (current)
		set_dynarray_value(argv, argv->count, current);
	return (argv);
}


