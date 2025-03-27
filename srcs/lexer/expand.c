#include "token.h"
#include "dynarray.h"
#include "env.h"
#include "libft.h"
#include "shell.h"
#include <stdio.h>

size_t	get_env_len(const char *str, size_t	key_len, t_shell *shell)
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

void	copy_env_value(const char *str, size_t key_len, t_shell *shell, char *new_value)
{
	
}

size_t	get_total_len(const char *str, t_shell *shell)
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
			str += key_len;
			if (env_len)
				total_len += env_len;
			continue;
		}
		total_len++;
		str++;
	}
	return (total_len);
}

char *create_new_value(const char *str, t_shell *shell)
{
	size_t	i;
	char	*new_value;
	size_t	key_len;

	new_value = malloc(sizeof(char) * (get_total_len(str, shell) + 1));
	if (!new_value)
		return (NULL);
	while (*str)
	{
		if (*str == '$')
		{
			key_len = parse_env_key_len(++str);
			if (key_len == 1 && *str == '?')
			{
				// new_value[i++] = ft_itoa_base(shell->exit_code, "0123456789");
				// get the exit code and convert it to string

				continue;
			}
			else if (key_len)
			{
				copy_env_value(str, key_len, shell, new_value);
				str += key_len;
				continue;
			}
			str += key_len;
			continue;
		}
		new_value[i++] = *str++;
	}
	new_value[i] = '\0';
	return (new_value);
}

void	expand_env(t_dynarray *arr, t_shell *shell)
{
	t_uint	i;
	t_token	*token;
	char	*new_value;

	i = 0;
	while (i < arr->count)
	{
		token = arr->data[i];
		if (token->type == TOKEN_VAR_TEXT 
			|| token->type == TOKEN_TEXT)
		{
			new_value = create_new_value(token->value, shell);
			if (new_value)
			{
				free(token->value);
				token->value = new_value;
				printf("Expanded value: %s\n", token->value);
			}
		}
		i++;
	}
}