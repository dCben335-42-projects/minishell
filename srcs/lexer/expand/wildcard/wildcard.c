#include "shell.h"
#include "token.h"
#include "struct_wildcard.h"
#include <stdio.h>
#include "libft.h"

char **match_wildcard_entries(t_wildcard *wildcard);





static char *get_wildcard(t_shell *shell, const char *value)
{
	t_wildcard	wildcard;
	char 	*content;
	char	***data;

	wildcard = init_wildcard(value, shell->current_path);
	if (!wildcard.pattern)
		return (NULL);
	data = (char ***) &wildcard.arr.data;
	if (!match_wildcard_entries(&wildcard) || !wildcard.arr.count)
		return (destroy_wildcard(&wildcard));
	printf("stored %u entries\n", wildcard.arr.count);
	ft_isort(*data, wildcard.arr.count, &ft_strcasecmp, FALSE);
	printf("sorted %u entries\n", wildcard.arr.count);
	if ((wildcard.is_prefix && !ft_strsaddprefix(wildcard.prefix, *data))
		|| (wildcard.is_suffix && !ft_strsaddsuffix(wildcard.suffix, *data)))
		return (destroy_wildcard(&wildcard));
	content = ft_strsjoin((const char **) wildcard.arr.data, wildcard.arr.count, " ");
	destroy_wildcard(&wildcard);
	return (content);
}


/**
 * @brief Expands TOKEN_TEXT tokens containing wildcards.
 *
 * @param shell The shell instance.
 * @param data The token to expand.
 */
void	*expand_wildcard_token(t_shell *shell, void *data)
{
	t_token	*token;
	char	*new_value;

	token = (t_token *)data;
	if (token->type == TOKEN_TEXT && ft_strchr(token->value, '*'))
	{
		new_value = get_wildcard(shell, token->value);
		if (!new_value)
			return (NULL);
		free(token->value);
		token->value = new_value;
	}
	return (NULL);
}