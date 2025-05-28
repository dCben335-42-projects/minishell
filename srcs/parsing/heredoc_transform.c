#include "parsing.h"
#include "minishell.h"
#include "minishell_signal.h"
#include "utils.h"

static t_ptr	handle_expandale_token(t_uint type)
{
    if (type == QUOTED_TEXT || type == QUOTED_EXPAND)
	{
		return (init_pointer(init_token(TEXT,
			HEREDOC_EXPANDABLE_FALSE,
			ft_strlen(HEREDOC_EXPANDABLE_FALSE)
		), TRUE));
	}
	return (init_pointer(init_token(TEXT, 
		HEREDOC_EXPANDABLE_TRUE,
		ft_strlen(HEREDOC_EXPANDABLE_TRUE)
	), TRUE));
}


static char	*trim_leading_tabs(char **str, char *line, t_bool is_first, t_bool need)
{
	char *start;
    char		*tmp;

	start = line;
	while (need && *start && *start == '\t')
		start++;
    if (is_first)
        tmp = ft_strdup(start);
    else
        tmp = ft_strsjoin((const char *[]){*str, start}, 2, "\n");
    free(*str);
    *str = tmp;
    if (!tmp)
        return (NULL);
    return (tmp);
}

static t_bool handle_loop(t_token *token, const char *readline_arg, t_bool need_trim)
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
		if (g_sig == SIGINT || !line || (!ft_strcmp(line, token->value) && !ft_free((void **)&line)))
			break ;
		if (!trim_leading_tabs(&str, line, is_first, need_trim) && !ft_free((void **)&line))
			return (FALSE);
		is_first = FALSE;
		free(line);
	}
	free(token->value);
	token->value = str;
	return (TRUE);
}


static t_bool heredoc_wrapper(t_token *token, const char *readline_arg, t_bool need_trim, t_bool *is_interrupted)
{
	const int	saved_stdin = dup(STDIN_FILENO);
	t_bool		ret;

	if (!saved_stdin)
		return (FALSE);
	signals(SIGCTX_HEREDOC);
	ret = handle_loop(token, readline_arg, need_trim);
	restore_std_in_out(saved_stdin, -1);
	signals(SIGCTX_SHELL);
	if (g_sig == SIGINT)
	{
		*is_interrupted = TRUE;
		g_sig = 0;
		return (FALSE);
	}
	return (ret);
}

/**
 * @brief Transforms a heredoc token by expanding it 
 * and reading input until the delimiter is reached.
 *
 * @param args The lexer arguments containing the tokens.
 * @param token The heredoc token to be transformed.
 * 
 * @note The token argument will be modified to contain the
 * heredoc content.
 * 
 * @return A pointer to the a token that indicate
 * if the heredoc is expandable or not.
*/
t_ptr	transform_heredoc(t_lexer_args *args, t_token *token)
{
	t_token	*prev;
	t_ptr	pointer;
	t_bool	need_trim;
	
	need_trim = args->is_heredoc == HEREDOC_TRIM;
	args->is_heredoc = NOT_HEREDOC;
	prev = args->tokens.data[args->tokens.count - 2];
	if (prev && prev->type == M_SPACE)
	   prev = args->tokens.data[args->tokens.count - 3];
   	pointer = handle_expandale_token(token->type);
	if (pointer.has_malloc_error)
		return (pointer);
    if (!prev || !heredoc_wrapper(token, get_readline_arg(prev->type), need_trim, &args->heredoc_interupted))
	{
		destroy_token(pointer.p);
		pointer.p = NULL;
		pointer.has_malloc_error = TRUE;
	}
    return (pointer);
}
