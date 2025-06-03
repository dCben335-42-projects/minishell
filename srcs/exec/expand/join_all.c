
#include "cmd_expand.h"

void	positivate_wildcard(char **str);
void	negate_wildcard(char **str);

char *handle_loop(t_shell *shell, t_dynarray *args, char *arg, const char *node_content)
{
	const t_bool is_last_spaced = *node_content && ft_isspace(node_content[ft_strlen(node_content) - 1]);
	char	**split;
	char	*tmp;
	size_t	i;

	i = 0;
	split = ft_split(node_content, ' ');
	if (!split)
	{
		free(arg);
		return (NULL);
	}
	while (split[i])
	{
		negate_wildcard(&split[i]);
		tmp = ft_strjoin(arg, split[i]);
		free(arg);
		if (tmp && (split[i + 1] || (!split[i + 1] && is_last_spaced)))
			tmp = save_expand_entry(shell, args, tmp, TRUE);
		if (!tmp)
		 	return (ft_free_split(split));
		arg = tmp;
		i++;
	}
	ft_free_split(split);
	return (arg);
}

t_bool is_quoted(t_ast_node *node)
{
	return (node->type & (CMD_QUOTED_TEXT | CMD_QUOTED_EXPAND));
}

char *join_env(t_shell *shell, t_dynarray *args, t_ast_node *node, char *arg, t_bool *is_wildcard)
{
	const char		*node_content = (const char *)node->content;
	const t_bool	is_space_start = ft_isspace(*node_content);
	const t_bool	is_space_end = *node_content && ft_isspace(node_content[ft_strlen(node_content) - 1]);

	if (is_space_start && (is_quoted(node) || *arg))
		arg = save_expand_entry(shell, args, arg, *is_wildcard);
	if (!arg)
		return (NULL);
	*is_wildcard = TRUE;
	if (is_space_end)
		*is_wildcard = FALSE;
	return (handle_loop(shell, args, arg, node_content));
}

char *join_standard(t_ast_node *node, char *arg, t_bool *is_wildcard)
{
	char	*node_content;
	char	*tmp;

	node_content = node->content;
	if (node->type & CMD_WILDCARD)
		*is_wildcard = TRUE;
	if (node->type & (CMD_TEXT | CMD_WILDCARD))
		negate_wildcard(&node_content);
	tmp = ft_strjoin(arg, node_content);
	free(arg);
	if (!tmp)
		return (NULL);
	return (tmp);
}




void *join_all(t_shell *shell, t_dynarray *word, t_dynarray *args)
{
	t_ast_node	*node;
	t_uint		i;
	t_bool		is_wildcard;
	char		*arg;

	i = 0;
	arg = ft_strdup("");
	if (!arg)
		return (NULL);
	is_wildcard = FALSE;
	while (i < word->count)
	{
		node = get_dynarray_value(word, i);
		if (node->type & CMD_EXPAND)
			arg = join_env(shell, args, node, arg, &is_wildcard);
		else
			arg = join_standard(node, arg, &is_wildcard);
		if (!arg)
			return (NULL);
		i++;
	}
	if (*arg || is_quoted(node))
		arg = save_expand_entry(shell, args, arg, is_wildcard);
	if (!arg)
		return (NULL);
	free(arg);
	return (args);
}
