/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:34:50 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/15 15:52:29 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "unistd.h"

static size_t	get_env_len(const char *str, size_t	key_len, t_shell *shell)
{
	t_env	*env;
	char	*substr;

	if (key_len == 1 && *str == '?')
		return (ft_intlen_base(shell->exit_code, 10));
	else if (key_len)
	{
		substr = ft_substr(str, 0, key_len);
		env = get_env_node(shell->env, substr);
		free(substr);
		if (env && env->value)
			return (ft_strlen(env->value));
	}
	return (0);
}

static size_t	get_total_len(const char *str, t_shell *shell)
{
	size_t	env_len;
	size_t	total_len;
	size_t	key_len;

	total_len = 0;
	while (*str)
	{
		if (*str == '$')
		{
			key_len = parse_env_key_len(++str);
			env_len = get_env_len(str, key_len, shell);
			str += key_len - 1;
			if (env_len)
				total_len += env_len - 1;
		}
		total_len++;
		str++;
	}
	return (total_len);
}

static char	*copy_env_value(
	const char *str,
	size_t key_len,
	t_shell *shell,
	char *dest
)
{
	t_env	*env;
	char	*substr;
	char	*tmp;

	if (key_len == 1 && *str == '?')
	{
		tmp = ft_itoa_base(shell->exit_code, "0123456789");
		if (!tmp)
			return (NULL);
		ft_strlcpy(dest, tmp, ft_strlen(tmp) + 1);
		free(tmp);
		return (dest);
	}
	else if (key_len)
	{
		substr = ft_substr(str, 0, key_len);
		if (!substr)
			return (NULL);
		env = get_env_node(shell->env, substr);
		free(substr);
		if (env && env->value)
			ft_strlcpy(dest, env->value, ft_strlen(env->value) + 1);
	}
	return (dest);
}

static char	*create_new_value(const char *str, char *dest, t_shell *shell)
{
	size_t	i;
	size_t	key_len;

	i = 0;
	while (*str)
	{
		dest[i] = '\0';
		if (*str == '$')
		{
			key_len = parse_env_key_len(++str);
			if (key_len)
			{
				if (!copy_env_value(str, key_len, shell, dest + i))
					return (ft_free((void **)dest));
				str += key_len;
				i += ft_strlen(dest + i);
				continue ;
			}
			str--;
		}
		dest[i++] = *str++;
	}
	dest[i] = '\0';
	return (dest);
}

#include "stdio.h"

void *loop_word(t_shell *shell, t_dynarray *word, void *(*f)(t_shell *, t_ast_node *))
{
	t_ast_node	*node;
	t_uint		i;

	i = 0;
	while (i < word->count)
	{
		node = (t_ast_node *)get_dynarray_value(word, i);
		if (!f(shell, node))
			return (NULL);
		i++;
	}
	return (word);
}

void *expand_env_node(t_shell *shell, t_ast_node *node)
{
	char	*new_value;
	const char *value = (const char *)node->content;

	if (node->type == CMD_EXPAND)
	{
		new_value = malloc((get_total_len(value, shell) + 1));
		if (!new_value)
			return (NULL);
		new_value = create_new_value(value, new_value, shell);
		if (!new_value)
			return (NULL);
		free(node->content);
		node->content = new_value;
	}
	return (node);
}

/**
 * @brief Expands the environment variables in the token.
 *
 * @param shell The shell instance.
 * @param arg The pointer to the string to expand.
 *
 * @return The expanded token or NULL if an error occurred.
*/
void	*expand_env_word(t_shell *shell, t_dynarray *word)
{
	return (loop_word(shell, word, expand_env_node));
}
