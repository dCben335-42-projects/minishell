#include "parsing.h"
#include "ast.h"
#include "minishell.h"
#include "fcntl.h"

static t_bool	is_command_finished(const char *input, t_token *token, t_lexer_args *args)
{
	if (token->rules & EXPECT_CONT || args->parenthesis.open > args->parenthesis.close)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			return (FALSE);
	}
	return (TRUE);
}

static t_pointer	get_next_token(t_lexer_args *args)
{
    int offset;

    while (*args->input)
    {
        if (args->quote == DELIMITER_EXPANDABLE_TEXT && *args->input == DELIMITER_EXPANDABLE_TEXT)
        {
            args->input++;
            args->quote = 0;
            continue ;
        }
        if (ft_isspace(*args->input) && args->quote == 0)
            return (tokenize_whitespace(args));
        offset = 0;
        return (get_token(args, offset, get_token_type(args->input, &offset)));
    }
	return (init_pointer(NULL, FALSE, FALSE));
}

static t_parse_status	get_parsing_error_status(
    t_lexer_args *args,
	t_pointer pointer
)
{
    t_parse_status  status;

	if (pointer.is_malloc && ((t_token *)pointer.pointer) == NULL)
		return (MALLOC_ERROR);
    status = token_parser(args, ((t_token *)pointer.pointer));
    if (status != COMMAND_VALID)
		return (status);
    if (!is_command_finished(args->input, ((t_token *)pointer.pointer), args))
		return (COMMAND_NOT_FINISHED);
    return (status);
}

t_parse_status heredoc_question(t_lexer_args *args, t_uint type)
{
    t_pointer       pointer;
    t_parse_status  status;

    if (type == QUOTED_TEXT || type == QUOTED_EXPAND)
        pointer = init_pointer(init_token(TEXT, HEREDOC_EXPANDABLE_FALSE, ft_strlen(HEREDOC_EXPANDABLE_FALSE)), TRUE, FALSE);
    else
        pointer = init_pointer(init_token(TEXT, HEREDOC_EXPANDABLE_TRUE, ft_strlen(HEREDOC_EXPANDABLE_TRUE)), TRUE, FALSE);
    status = get_parsing_error_status(args, pointer);
    return (status);
}	

char *heredoc_join(char **str, char *line, t_bool is_first)
{
    const char *joined[2] = {*str, line};
    char *tmp;

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

char *remove_indent_tab_heredoc(char **str, char *line, t_bool is_first, t_bool is_trimmed)
{
	char *start;

	start = line;
	while (is_trimmed && *start && *start == '\t')
		start++;
	return (heredoc_join(str, start, is_first));
}

t_parse_status  heredoc_sample(t_lexer_args *args, t_token *token)
{
    t_bool  is_first;
    char    *str;
    char    *line;
    
    heredoc_question(args, token->type);
    str = ft_strdup("");
    if (!str)
        return (MALLOC_ERROR);
    is_first = TRUE;
    while (TRUE) 
{
        line = readline(SHELL_NEXT_NAME);
        if (!line || (!ft_strcmp(line, token->value) && !ft_free((void *)&line)))
            break ;
        if (!remove_indent_tab_heredoc(&str, line, is_first, args->is_heredoc == HEREDOC_TRIM) && !ft_free((void *)&line))
            return (MALLOC_ERROR);
        is_first = FALSE;
		free(line);
    }
    free(token->value);
    token->value = str;
	args->is_heredoc = NOT_HEREDOC;
    return (COMMAND_VALID);
}   	

t_parse_status    lexer(t_lexer_args *args)
{
    t_pointer		pointer;
    t_parse_status	status;
    t_pointer       pointer2;

    pointer = get_next_token(args);
    while (pointer.pointer)
    {
		status = get_parsing_error_status(args, pointer);
        if (status != COMMAND_VALID)
            return (status);
        if (args->is_heredoc && is_text_token(*((t_token *)pointer.pointer)))
            heredoc_sample(args, pointer.pointer);
		pointer = get_next_token(args);
    }
    pointer2 = init_pointer(init_token(M_EOF, "newline", 7), TRUE, FALSE);
    if (((t_token *)pointer2.pointer) == NULL)
        return (MALLOC_ERROR);
    return (token_parser(args, ((t_token *)pointer2.pointer)));
}




// ( ( ( echo jojo$PATH'$GOOD'"okksa   'fjeifj'          iji*ji$HELLO"jigo/*'ffe'./?out) )&& echo $'bonjour'"salut $" )
// bash: erreur de syntaxe : fin de fichier prématurée