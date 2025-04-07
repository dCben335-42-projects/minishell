#include "shell.h"
#include "token.h"
#include "struct_wildcard.h"
#include <stdio.h>

char **match_wildcard_entries(const char *path, const char *pattern, t_dynarray *arr);

/*
 * @brief Checks if the string is a path.
 *
 * @param str The string to check.
 * @return TRUE if the string is a path, FALSE otherwise.
 */
// t_bool	ft_ispath(const char *str)
// {
// 	if (*str == '/'
// 		|| !ft_strncmp(str, "./", 2)
// 		|| !ft_strncmp(str, "../", 3)
// 	)
// 		return (TRUE);
// 	return (FALSE);
// }

/**
 * @brief Adds a prefix to each string in the array.
 *
 * @param prefix The prefix to add.
 * @param content The array of strings.
 * @return The modified array of strings with the prefix added.
 * 	NULL if memory allocation fails.
 */
static char	**ft_strsaddprefix(const char *prefix, char **content)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (content[i])
	{
		tmp = ft_strjoin(prefix, content[i]);
		if (!tmp)
			return (NULL);
		free(content[i]);
		content[i] = tmp;
		i++;
	}
	return (content);
}

/**
 * @brief Adds a suffix to each string in the array.
 *
 * @param suffix The suffix to add.
 * @param content The array of strings.
 * @return The modified array of strings with the suffix added.
 * 	NULL if memory allocation fails.
 */
static char	**ft_strsaddsuffix(const char *suffix, char **content)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (content[i])
	{
		tmp = ft_strjoin(content[i], suffix);
		if (!tmp)
			return (NULL);
		free(content[i]);
		content[i] = tmp;
		i++;
	}
	return (content);
}

char *get_wildcard(t_shell *shell, const char *value)
{
	t_wildcard	wildcard;
	char 	*content;

	wildcard = init_wildcard(value, shell->current_path);
	if (wildcard.is_error)
		return (NULL);
	printf("prefix: %s\n", wildcard.prefix);
	printf("suffix: %s\n", wildcard.suffix);
	printf("pattern: %s\n", wildcard.pattern);
	printf("base_path: %s\n", wildcard.base_path);
	printf("is_prefix: %d\n", wildcard.is_prefix);
	printf("is_suffix: %d\n", wildcard.is_suffix);
	if (!match_wildcard_entries(wildcard.base_path, wildcard.pattern, &wildcard.arr) || !wildcard.arr.count)
		return (destroy_wildcard(&wildcard));
	ft_isort((char **)wildcard.arr.data, wildcard.arr.count, &ft_strcasecmp, FALSE);
	if (wildcard.is_prefix )
	{
		if (!ft_strsaddprefix(wildcard.prefix, (char **)wildcard.arr.data))
			return (destroy_wildcard(&wildcard));
	}
	if (wildcard.is_suffix)
	{
		if (!ft_strsaddsuffix(wildcard.suffix, (char **)wildcard.arr.data))
			return (destroy_wildcard(&wildcard));
	}
	content = ft_strsjoin((const char **)wildcard.arr.data, wildcard.arr.count, TRUE);
	destroy_wildcard(&wildcard);
	return (content);
}


// static void *free_interpret_wildcard_pattern(t_dynarray *arr, char *path, char *extracted_path)
// {
// 	if (extracted_path)
// 	{
// 		free(path);
// 		free(extracted_path);
// 	}
// 	destroy_dynarray(arr);
// 	return (NULL);
// }

// char *interpret_wildcard_pattern(t_shell *shell, const char *pattern)
// {
// 	t_dynarray	arr;
// 	char		*content;
// 	char 		*path;
// 	char		*extracted_path;

// 	path = shell->current_path;
// 	extracted_path = NULL;
// 	if (ft_ispath(pattern))
// 	{
// 		path = get_right_path(&pattern, shell->current_path, &extracted_path);
// 		if (!path)
// 			return (NULL);
// 	}
// 	arr = init_dynarray(1, &handle_free);
// 	if ((!match_wildcard_entries(path, pattern, &arr) || !arr.count))
// 		return (free_interpret_wildcard_pattern(&arr, path, extracted_path));
// 	ft_isort((char **)arr.data, arr.count, &ft_strcasecmp, FALSE);
// 	if (extracted_path)
// 		if (!ft_strsaddprefix(extracted_path, (char **)arr.data))
// 			return (free_interpret_wildcard_pattern(&arr, path, extracted_path));
// 	content = ft_strsjoin((const char **)arr.data, arr.count, TRUE);
// 	free_interpret_wildcard_pattern(&arr, path, extracted_path);;
// 	return (content);
// }


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