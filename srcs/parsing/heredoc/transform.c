/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:40:35 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/20 16:51:19 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static t_ptr	get_start_token(t_lexer_args *args)
{
	t_ptr		ptr;

	ptr = get_next_token(args);
	while (ptr.p && is_meta_token(ptr.p))
	{
		destroy_token(ptr.p);
		ptr = get_next_token(args);
	}
	return (ptr);
}

static char	*get_delmiter(
	t_lexer_args *args,
	t_ptr *ptr,
	t_ptr *after_ptr,
	t_bool *is_expandable
)
{
	t_ptr	next_ptr;
	char	*delimiter;
	char	*tmp;

	delimiter = ft_strdup("");
	while (ptr->p && is_text_token(ptr->p))
	{
		if (is_quoted_text_token(ptr->p))
			*is_expandable = TRUE;
		tmp = ft_strjoin(delimiter, ((t_token *)(ptr->p))->value);
		free(delimiter);
		if (!tmp)
			return (NULL);
		delimiter = tmp;
		next_ptr = get_next_token(args);
		if (!next_ptr.p || !is_text_token(next_ptr.p))
		{
			get_parsing_error_status(args, *ptr);
			break ;
		}
		destroy_token(ptr->p);
		*ptr = next_ptr;
	}
	*after_ptr = next_ptr;
	return (delimiter);
}

/**
 * @brief Reads a heredoc from the cached values if available.
 *
 * @param args The lexer arguments containing the cached heredoc values.
 * @param token The token to be filled with the heredoc value.
 * 
 * @return 1 if a heredoc was read, 0 if not, -1 on error.
*/
int	read_heredoc_if_possible(t_lexer_args *args, t_token *token)
{
	const t_uint	i = args->heredoc_ckey;
	char			*cache_heredoc;

	cache_heredoc = (char *)get_dynarray_value(args->heredoc_cval, i);
	args->heredoc_ckey++;
	if (cache_heredoc)
	{
		free(token->value);
		token->value = ft_strdup(cache_heredoc);
		if (!token->value)
			return (-1);
		return (1);
	}
	return (0);
}

/**
 * @brief Transforms a heredoc token by expanding it 
 * and reading input until the delimiter is reached.
 *
 * @param args The lexer arguments containing the tokens.
 * @param token The heredoc token to be transformed.
 * 
 * @note It will get the next token until it finds something different
 * than a text token, which is the delimiter of the heredoc.
 * 
 * @note The token value is containing the delimiter
 * and the heredoc content will be read from the user input and
 * then stored in the token value.
 * 
 * @return A pointer to the next token after the HEREDOC
*/
t_ptr	transform_heredoc(t_lexer_args *args)
{
	t_ptr			ptr;
	t_ptr			after_ptr;
	t_bool			is_expandable;
	char			*delimiter;
	t_parse_status	status;

	ptr = get_start_token(args);
	status = COMMAND_VALID;
	if (!ptr.p || !is_text_token(ptr.p))
		return (ptr);
	is_expandable = FALSE;
	delimiter = get_delmiter(args, &ptr, &after_ptr, &is_expandable);
	free(((t_token *)(ptr.p))->value);
	((t_token *)(ptr.p))->value = delimiter;
	if (delimiter)
		status = read_heredoc(args, ptr.p, is_expandable);
	if (delimiter && status != MALLOC_ERROR)
		return (after_ptr);
	destroy_token(after_ptr.p);
	return (init_pointer(NULL, TRUE));
}
