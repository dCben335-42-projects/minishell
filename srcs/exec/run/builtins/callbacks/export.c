/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:30:22 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 02:43:25 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_builtin.h"
#include "libft.h"
#include "config.h"
#include "utils.h"

static void	process_env(t_shell *shell, char *key, char *arg)
{
	const t_env	*matched_env = get_env_node(shell->env, key);
	char		*value;
	char		*complete_value;
	char		*parsed_value;

	if (!matched_env)
	{
		add_env_node(&shell->env, init_env_node(arg));
		return ;
	}
	parsed_value = parse_env_value(arg);
	value = parsed_value;
	if (!value)
		value = ft_strdup("");
	if (!p_ptr(value, ERROR_MALLOC))
		return ;
	complete_value = value;
	if ((arg[ft_strlen(key)] == '+') && matched_env->value)
	{
		complete_value = ft_strjoin(matched_env->value, value);
		free(value);
	}
	if (!parsed_value || !complete_value
		|| !add_existing_env(shell->env, key, complete_value))
		free(complete_value);
}

static t_bool	is_valid_export(t_shell *shell, char **args)
{
	char	*key;
	size_t	i;
	t_bool	is_valid;

	i = 1;
	is_valid = TRUE;
	while (args[i])
	{
		key = parse_env_key(args[i]);
		if (!key)
		{
			is_valid = FALSE;
			printf(ERR_EXPORT_ID, args[i]);
		}
		else
			process_env(shell, key, args[i]);
		free(key);
		i++;
	}
	return (is_valid);
}

/**
 * 
 * @brief Exports the environment variables to the shell.
 *
 * @param shell The shell instance.
 * @param args The arguments to the command.
 * 
 * @note This function checks if the arguments are valid and
 * exports them to the shell. If no arguments are provided,
 * it will print the current environment variables.
 * 
 * @note If one of the arguments is invalid, it will print an
 * error message and return a non-zero exit code.
 * 
 */
void	ft_export(t_shell *shell, char **args)
{
	if (!args[1])
		read_env(shell->env, TRUE);
	shell->exit_code = !is_valid_export(shell, args);
	destroy_dynarray(&shell->env_array);
	shell->env_array = env_to_array(shell->env);
}
