#include "utils.h"
#include "messages.h"

static const char	*handle_pwd_user(char *user_value, char *pwd, t_bool is_home_based)
{
	if (is_home_based)
	{
		return (ft_strsjoin((const char *[]){
			FIRST_COL_RL, user_value, RESET_COL_RL, ":",
			SECOND_COL_RL, "~/", pwd, RESET_COL_RL, "$ "
		}, 9, ""));
	}
	return (ft_strsjoin((const char *[]){
		FIRST_COL_RL, user_value, RESET_COL_RL, ":",
		SECOND_COL_RL, pwd, RESET_COL_RL, "$ "
	}, 8, ""));
}

static const char	*handle_pwd_no_user(char *pwd, t_bool is_home_based)
{
	if (is_home_based)
	{
		return (ft_strsjoin((const char *[]){
			FIRST_COL_RL, SHELL_NAME, RESET_COL_RL, ":",
			SECOND_COL_RL, "~/", pwd, RESET_COL_RL, "$ "
		}, 9, ""));
	}
	return (ft_strsjoin((const char *[]){
		FIRST_COL_RL, SHELL_NAME, RESET_COL_RL, ":",
		SECOND_COL_RL, pwd, RESET_COL_RL, "$ "
	}, 8, ""));
}

static char	*get_correct_pwd(const t_env *home, char *pwd, t_bool *is_home_based)
{
	size_t	home_len;

	*is_home_based = FALSE;
	if (home && home->value)
	{
		home_len = ft_strlen(home->value);
		if (!ft_strncmp(home->value, pwd, home_len) && home_len > 1)
		{
			if (pwd[home_len] != '/')
				return (pwd);
			pwd += home_len + 1;
			*is_home_based = TRUE;
		}
	}
	return (pwd);
}

/**
 * @brief Generates the main readline prompt argument.
 *
 * @param shell The shell structure containing the current state.
 *
 * @note If there is no current path, it will use the user name
 * 	 from the environment variable USER or the shell name.
 * 
 * @note Otherwise, it will use the current path and the user name
 * 	 and the HOME environment variable to determine if the path is
 * 	 home-based or not.
 * 
 * @note The prompt will be formatted with colors:
 * 
 * @return The generated readline prompt argument.
 */
const char *get_main_readline_arg(t_shell *shell)
{
	const t_env	*user = get_env_node(shell->env, ENV_USER_KEY);
	const t_env	*home = get_env_node(shell->env, ENV_HOME_KEY);
	t_bool		is_home_based;
	char		*pwd;

	pwd = shell->current_path;
	if (pwd)
	{
		pwd = get_correct_pwd(home, pwd, &is_home_based);
		if (user && user->value)
			return (handle_pwd_user(user->value, pwd, is_home_based));
		return (handle_pwd_no_user(pwd, is_home_based));
	}
	else if (user && user->value)
		return (ft_strsjoin((const char *[]){FIRST_COL_RL, user->value, RESET_COL_RL, "$ "}, 4, ""));
	return (ft_strsjoin((const char *[]){FIRST_COL_RL, SHELL_NAME, RESET_COL_RL, "$ "}, 4, ""));
}
