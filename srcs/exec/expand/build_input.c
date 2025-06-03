/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:13:00 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:18 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"

// static char	*get_value(char *content, char *input, t_bool is_first)
// {
// 	char	*val;
// 	char	*tmp;

// 	tmp = NULL;
// 	printf("get_value: content = '%s', input = '%s\n", content, input);
// 	if (ft_strchr(content, SYMBOL_GLOB_ANY))
// 		val = ft_strdup(content);
// 	else
// 		val = ft_strsjoin((const char *[]){"\"", content, "\""}, 3, NULL);
// 	printf("get_value: val = '%s'\n", val);
// 	if (!val)
// 	{
// 		free(input);
// 		return (NULL);
// 	}
// 	if (is_first)
// 		tmp = ft_strsjoin((const char *[]){input, val}, 2, NULL);
// 	else
// 		tmp = ft_strsjoin((const char *[]){input, " ", val}, 3, NULL);
// 	free(input);
// 	free(val);
// 	if (!tmp)
// 		return (NULL);
// 	printf("get_value: tmp=|%s|\n", tmp);
// 	return (tmp);	
// }

// static char	*build_wildcard(t_ast_node *node, char *input)
// {
// 	char	**splitted;
// 	size_t	i;
	
// 	splitted = ft_split(node->content, ' ');
// 	if (!splitted)
// 	{
// 		free(input);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (splitted[i])
// 	{
// 		input = get_value(splitted[i], input, i == 0);
// 		if (!input)
// 			return (ft_free_split(splitted));
// 		i++;
// 	}
// 	ft_free_split(splitted);
// 	return (input);
// }


// static char *build_standart(t_ast_node *node, char *input)
// {
// 	char	*tmp;

// 	if (node->type == CMD_TEXT)
// 		tmp = ft_strjoin(input, node->content);
// 	else if (ft_strchr(node->content, '\''))
// 		tmp = ft_strsjoin((const char *[]){input, "\"", node->content, "\""}, 4, NULL);
// 	else
// 		tmp = ft_strsjoin((const char *[]){input, "'", node->content, "'"}, 4, NULL);
// 	free(input);
// 	if (!tmp)
// 		return (NULL);
// 	return (tmp);
// }

// char	*build_expand_input(t_dynarray *word)
// {
// 	t_ast_node	*node;
// 	char		*input;
// 	t_uint		i;
	
// 	input = ft_strdup("");
// 	if (!input)
// 		return (NULL);
// 	i = 0;
// 	while (i < word->count)
// 	{
// 		node = get_dynarray_value(word, i);
// 		if (is_node_wildcard(node))
// 			input = build_wildcard(node, input);
// 		else
// 			input = build_standart(node, input);
// 		if (!input)
// 			return (NULL);
// 		i++;
// 	}
// 	return (input);
// }
