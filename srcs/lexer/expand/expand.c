#include "minishell.h"

void	expand_env(t_dynarray *arr, t_shell *shell)
{
	loop_dynarray(arr, shell, &expand_env_token);
}

void	expand_wildcard(t_dynarray *arr, t_shell *shell)
{
	loop_dynarray(arr, shell, &expand_wildcard_token);
}