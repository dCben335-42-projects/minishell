/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:34:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/06 03:05:53 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "unistd.h"
#include "utils.h"


/**
 * @brief Expands the environment variables in a string.
 *
 * @param shell The shell instance that contains the environment.
 * @param str The string to expand.
 * 
 * @note This function iterates through the string and expands
 * the environment variables. It directly free the old content
 * of the string and replaces it with the new expanded value.
 * 
 * @return The expanded string or NULL if an error occurred.
 */
char	*expand_env_str(t_shell *shell, char **str)
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

/**
 * @brief Expands the environment variables in a word.
 *
 * @param shell The shell instance that contains the environment.
 * @param word The word to expand.
 * 
 * @note This function iterates through the word and expands
 * the environment variables in each node. It directly free the
 * old content of the node and replaces it with the new
 * expanded value.
 * 
 * @return The expanded word or NULL if an error occurred.
 */
void	*expand_env_word(t_shell *shell, t_dynarray *word)
{
	t_ast	*node;
	t_uint		i;
	
	i = 0;
	while (i < word->count)
	{
		node = (t_ast *)get_dynarray_value(word, i);
		if ((node->type == CMD_EXPAND || node->type == CMD_QUOTED_EXPAND)
			&& !expand_env_str(shell, (char **)&node->content))
			return (NULL);
		i++;
	}
	return (word);
}
