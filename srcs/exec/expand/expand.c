/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:10:10 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/15 23:52:29 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_expand.h"
#include "config.h"

static char	*handle_loop(
	t_shell *shell,
	t_dynarray *args,
	char *arg,
	const char *content
)
{
	const t_bool	is_last_spaced = *content
		&& ft_isspace(content[ft_strlen(content) - 1]);
	const char		charset[] = {SYMBOL_GLOB_ANY, SYMBOL_GLOB_ONE, '\0'};
	char			**split;
	char			*tmp;
	size_t			i;

	i = 0;
	split = ft_split(content, " \t\n\v\f\r");
	if (!split)
		return (ft_free((void **)&arg));
	while (split[i])
	{
		ft_strnegate(&split[i], charset);
		tmp = ft_strjoin(arg, split[i]);
		free(arg);
		if (tmp && (split[i + 1] || (!split[i + 1] && is_last_spaced)))
			tmp = save_expand(shell, args, tmp, TRUE);
		if (!tmp)
			return (ft_strsfree(split));
		arg = tmp;
		i++;
	}
	ft_strsfree(split);
	return (arg);
}

static char	*join_and_save_env(
	t_shell *shell,
	t_dynarray *args,
	t_expand_ctx *ctx
)
{
	const char		*content = ctx->curr_node->content;
	const size_t	content_len = ft_strlen(content) - 1;
	const t_bool	is_space_start = ft_isspace(*content);
	const t_bool	is_space_end = *content && ft_isspace(content[content_len]);

	if (is_space_start && (*ctx->arg || ctx->is_quoted))
		ctx->arg = save_expand(shell, args, ctx->arg, ctx->is_wildcard);
	if (!ctx->arg)
		return (NULL);
	if (*content)
		ctx->is_quoted = FALSE;
	if (is_space_end)
		ctx->is_wildcard = FALSE;
	else
		ctx->is_wildcard = TRUE;
	return (handle_loop(shell, args, ctx->arg, content));
}

static char	*join_standard(t_expand_ctx *ctx)
{
	const t_node_type	type = ctx->curr_node->type;
	const char			charset[] = {SYMBOL_GLOB_ANY, SYMBOL_GLOB_ONE, '\0'};
	char				*content;
	char				*tmp;

	content = ctx->curr_node->content;
	if (type & CMD_WILDCARD)
		ctx->is_wildcard = TRUE;
	if (type & (CMD_QUOTED_TEXT | CMD_QUOTED_ENV))
		ctx->is_quoted = TRUE;
	if (type & (CMD_TEXT | CMD_WILDCARD))
		ft_strnegate(&content, charset);
	tmp = ft_strjoin(ctx->arg, content);
	free(ctx->arg);
	return (tmp);
}

static t_dynarray	*join_all(t_shell *shell,
	t_dynarray *args,
	t_dynarray *word,
	t_expand_ctx *ctx
)
{
	t_uint	i;

	i = 0;
	while (i < word->count)
	{
		ctx->curr_node = get_dynarray_value(word, i);
		if (ctx->curr_node->type & CMD_ENV)
			ctx->arg = join_and_save_env(shell, args, ctx);
		else
			ctx->arg = join_standard(ctx);
		if (!ctx->arg)
			return (NULL);
		i++;
	}
	if (*ctx->arg || ctx->is_quoted)
		ctx->arg = save_expand(shell, args, ctx->arg, ctx->is_wildcard);
	if (!ctx->arg)
		return (NULL);
	free(ctx->arg);
	return (args);
}

/**
 * @brief Expands a word in the shell context.
 * 
 * This function checks if the word is an environment variable or a wildcard.
 *
 * @param shell The shell context containing environment variables.
 * @param word The word to be expanded, represented as a dynamic array.
 * @param args The array to store the expanded arguments.
 * 
 * @return The last args element or NULL if an error occurs.
*/
t_dynarray	*expand_word(t_shell *shell, t_dynarray *word, t_dynarray *args)
{
	t_expand_ctx	ctx;

	if (!expand_env_word(shell, word))
		return (NULL);
	ctx.arg = ft_strdup("");
	if (!ctx.arg)
		return (NULL);
	ctx.curr_node = NULL;
	ctx.is_wildcard = FALSE;
	ctx.is_quoted = FALSE;
	return (join_all(shell, args, word, &ctx));
}
