/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 01:09:12 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 21:26:48 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell_signal.h"
#include "utils.h"
#include "readline/readline.h"

static t_ptr	handle_expandale_token(t_bool is_expandable)
{
	if (is_expandable)
	{
		return (init_pointer(init_token(TEXT, \
			HEREDOC_EXPANDABLE_FALSE, \
			ft_strlen(HEREDOC_EXPANDABLE_FALSE) \
		), TRUE));
	}
	return (init_pointer(init_token(TEXT, \
		HEREDOC_EXPANDABLE_TRUE, \
		ft_strlen(HEREDOC_EXPANDABLE_TRUE) \
	), TRUE));
}

static char	*trim_leading_tabs(
	char **str,
	char *line,
	t_bool is_first,
	t_bool need
)
{
	char	*start;
	char	*tmp;

	start = line;
	while (need && *start && *start == '\t')
		start++;
	if (is_first)
		tmp = ft_strdup(start);
	else
		tmp = ft_strsjoin((const char *[]){*str, start}, 2, "\n");
	free(*str);
	*str = tmp;
	return (tmp);
}

static t_bool	handle_loop(
	t_token *token,
	const char *readline_arg,
	const t_bool need_trim
)
{
	t_bool		is_first;
	char		*str;
	char		*line;

	str = ft_strdup("");
	if (!str)
		return (FALSE);
	is_first = TRUE;
	while (TRUE)
	{
		line = readline(readline_arg);
		if ((g_sig == SIGINT || !line || !ft_strcmp(line, token->value))
			&& !ft_free((void **)&line))
			break ;
		if (!trim_leading_tabs(&str, line, is_first, need_trim)
			&& !ft_free((void **)&line))
			return (FALSE);
		is_first = FALSE;
		free(line);
	}
	free(token->value);
	token->value = str;
	return (TRUE);
}

static t_bool	heredoc_wrapper(
	t_lexer_args *args,
	t_token *token,
	const char *readline_arg,
	const t_bool need_trim
)
{
	const int	saved_stdin = dup(STDIN_FILENO);
	t_bool		ret;
	char		*tmp;

	tmp = NULL;
	if (!saved_stdin)
		return (FALSE);
	signals(SIGCTX_HEREDOC);
	ret = handle_loop(token, readline_arg, need_trim);
	restore_std_in_out(saved_stdin, -1);
	signals(SIGCTX_SHELL);
	if (g_sig == SIGINT)
	{
		args->interrupted = TRUE;
		g_sig = 0;
		return (FALSE);
	}
	if (ret)
		tmp = ft_strdup(token->value);
	if (!ret || !tmp || !push(args->heredoc_cval, tmp))
	{
		free(tmp);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Transforms a heredoc token by expanding it 
 * and reading input until the delimiter is reached.
 *
 * @param args The lexer arguments containing the tokens.
 * @param token The heredoc token to be transformed.
 * 
 * @note The token value is containing the delimiter
 * and the heredoc content will be read from the user input and
 * then stored in the token value.
 * 
 * @return A pointer to the a token that indicate
 * if the heredoc is expandable or not.
*/
t_parse_status	read_heredoc(
	t_lexer_args *args,
	t_token *token,
	const t_bool is_expandable
)
{
	const t_bool		need_trim = args->is_heredoc == HEREDOC_TRIM;
	t_ptr				pointer;
	int					ret;
	t_token_type		type;

	type = (t_token_type) args->is_heredoc;
	args->is_heredoc = NOT_HEREDOC;
	pointer = handle_expandale_token(is_expandable);
	if (pointer.has_malloc_error)
		return (MALLOC_ERROR);
	ret = read_heredoc_if_possible(args, token);
	if (ret == 0
		&& !heredoc_wrapper(args, token, get_readline_arg(type), need_trim))
		ret = -1;
	if (ret == -1)
	{
		if (pointer.p)
			destroy_token(pointer.p);
		pointer = init_pointer(NULL, TRUE);
	}
	return (get_parsing_error_status(args, pointer));
}
