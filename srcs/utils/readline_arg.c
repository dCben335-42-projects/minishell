#include "utils.h"
#include "messages.h"

static const char	*handle_pwd_user(char *user_value, char *pwd, t_bool is_home_based)
{
	if (is_home_based)
	{
		return (ft_strsjoin((const char *[]){
			FIRST_COL, user_value, RESET_COL, ":",
			SECOND_COL, "~/", pwd, RESET_COL, "$ "
		}, 9, ""));
	}
	return (ft_strsjoin((const char *[]){
		FIRST_COL, user_value, RESET_COL, ":",
		SECOND_COL, pwd, RESET_COL, "$ "
	}, 8, ""));
}

static const char	*handle_pwd_no_user(char *pwd, t_bool is_home_based)
{
	if (is_home_based)
	{
		return (ft_strsjoin((const char *[]){
			FIRST_COL, SHELL_NAME, RESET_COL, ":",
			SECOND_COL, "~/", pwd, RESET_COL, "$ "
		}, 9, ""));
	}
	return (ft_strsjoin((const char *[]){
		FIRST_COL, SHELL_NAME, RESET_COL, ":",
		SECOND_COL, pwd, RESET_COL, "$ "
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

const char *get_main_readline_arg(t_shell *shell)
{
	const t_env	*user = get_env_node(shell->env, USER_KEY);
	const t_env	*home = get_env_node(shell->env, HOME_KEY);
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
		return (ft_strsjoin((const char *[]){FIRST_COL, user->value, RESET_COL, "$ "}, 4, ""));
	return (ft_strsjoin((const char *[]){FIRST_COL, SHELL_NAME, RESET_COL, "$ "}, 4, ""));
}
