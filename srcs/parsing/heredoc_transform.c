#include "parsing.h"
#include "minishell.h"

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

static char	*heredoc_join(char **str, char *line, t_bool is_first)
{
    const char	*joined[2] = {*str, line};
    char		*tmp;

    if (is_first)
        tmp = ft_strdup(line);
    else
        tmp = ft_strsjoin(joined, 2, "\n");
    free(*str);
    *str = tmp;
    if (!tmp)
        return (NULL);
    return (tmp);
}

static char	*trim_leading_tabs(char **str, char *line, t_bool is_first, t_bool need)
{
	char *start;

	start = line;
	while (need && *start && *start == '\t')
		start++;
	return (heredoc_join(str, start, is_first));
}

t_bool handle_loop(t_token *token)
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
		line = readline(SHELL_NEXT_NAME);
		if (!line || (!ft_strcmp(line, token->value) && !ft_free((void **)&line)))
			break ;
		if (!trim_leading_tabs(&str, line, is_first, TRUE) && !ft_free((void **)&line))
			return (FALSE);
		is_first = FALSE;
		free(line);
	}
	free(token->value);
	token->value = str;
	return (TRUE);
}

t_ptr	transform_heredoc(t_lexer_args *args, t_token *token)
{
	t_ptr	pointer;
    
	args->is_heredoc = NOT_HEREDOC;
   	pointer = handle_expandale_token(token->type);
    if (!handle_loop(token))
	{
		destroy_token(pointer.p);
		pointer.p = NULL;
		pointer.has_malloc_error = TRUE;
	}
    return (pointer);
}
