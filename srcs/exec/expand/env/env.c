/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:34:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/16 18:19:05 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "unistd.h"
#include "utils.h"

char *expand_env_str(t_shell *shell, char **str)
{
	char	*new_value;
	size_t	total_len;

	total_len = determine_env_length(*str, shell);
	new_value = malloc((total_len + 1) * sizeof(char));
	if (!new_value)
		return (NULL);
	new_value = cpy_env(*str, new_value, shell);
	if (!new_value)
		return (NULL);
	free(*str);
	*str = new_value;
	return (*str);
}

void	*expand_env_word(t_shell *shell, t_dynarray *word)
{
	t_ast_node	*node;
	t_uint		i;
	
	i = 0;
	while (i < word->count)
	{
		node = (t_ast_node *)get_dynarray_value(word, i);
		if (node->type == CMD_EXPAND && !expand_env_str(shell, (char **)&node->content))
			return (NULL);
		i++;
	}
	return (word);
}
