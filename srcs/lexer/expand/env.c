#include "shell.h"
#include "libft.h"
#include "env.h"
#include "token.h"

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
			str += key_len - 1;
			if (env_len)
				total_len += env_len - 1;
		}
		total_len++;
		str++;
	}
	return (total_len);
}

char	*copy_env_value(const char *str, size_t key_len, t_shell *shell, char *new_value)
{
	t_env	*env;
	char	*substr;
	char	*tmp;

	if (key_len == 1 && *str == '?')
	{
		tmp = ft_itoa_base(shell->exit_code, "0123456789");
		if (!tmp)
			return (NULL);
		ft_strlcpy(new_value, tmp, ft_strlen(tmp) + 1);
		free(tmp);
		return (new_value);
	}
	else if (key_len)
	{
		substr = ft_substr(str, 0, key_len);
		if (!substr)
			return (NULL);
		env = get_env_node(shell->env, substr);
		free(substr);
		if (env && env->value)
			ft_strlcpy(new_value, env->value, ft_strlen(env->value) + 1);
	}
	return (new_value);
}

static char	*create_new_value(const char *str, char *new_value, t_shell *shell)
{
    size_t	i;
    size_t	key_len;

	i = 0;
    while (*str)
    {
        new_value[i] = '\0';
        if (*str == '$')
        {
            key_len = parse_env_key_len(++str);
            if (key_len)
			{
				if (!copy_env_value(str, key_len, shell, new_value + i))
					return (ft_handle_free((void **)new_value));
				str += key_len;
				i += ft_strlen(new_value + i);
				continue;
			}
			str--;
        }
		new_value[i++] = *str++;
    }
    new_value[i] = '\0';
    return (new_value);
}

void	*expand_env_token(t_shell *shell, void *data)
{
	t_token	*token;
	char	*new_value;

	token = (t_token *)data;
	if (token->type == TOKEN_TEXT || token->type == TOKEN_VAR_TEXT)
	{
		new_value = malloc(sizeof(char) * (get_total_len(token->value, shell) + 1));
		if (!new_value)
			return (NULL);
		new_value = create_new_value(token->value, new_value, shell);
		if (!new_value)
			return (NULL);
		free(token->value);
		token->value = new_value;
	}
	return (NULL);
}

