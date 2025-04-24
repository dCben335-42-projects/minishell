#include "parsing.h"

t_token	*handler_token_text(size_t *i, t_lexer_args *args)
{
	size_t	start_i;

	start_i = *i;
	while (args->input[*i] && !ft_isspace(args->input[*i])
		&& get_token_type(&args->input[*i], 0) == TOKEN_TEXT)
    {
        if (args->input[*i] == DQUOTE)
        {
            if (args->quote != QUOTE)
            {
                args->quote = DQUOTE;
                break ;
            }
            else
                (*i)++;
        }
        if (args->input[*i] == QUOTE)
        {
            if (args->quote != DQUOTE)
            {
                args->quote = QUOTE;
                break ;
            }
            else
                (*i)++;
        }
		(*i)++;
    }
	return (init_token(TOKEN_TEXT, args->input, start_i, *i - start_i));
}






























/* static t_parse_status	get_parsing_error_status(
	t_token *token,
	t_lexer_args *args,
	size_t *i
)
{
	t_parse_status	status;

	if (!token)
		return (COMMAND_NOT_VALID);
	status = token_parser(args, token);
	if (status != COMMAND_VALID)
		return (status);
	if (!is_command_finished(&args->input[*i], token))
		return (COMMAND_NOT_FINISHED);
	return (status);
} */



static t_token	*get_token(
	t_lexer_args *args,
	size_t *i,
	int offset,
	t_token_type_flags type
)
{
	if (type == TOKEN_TEXT)
		return (handler_token_text(i, args));
}

static t_token *get_isspace_token(t_lexer_args *args, size_t *i)
{
    while (ft_isspace(args->input[*i]))
        (*i)++;
    return (init_token(TOKEN_SPACE, "", 0, 0));
}

t_token *get_next_token(t_lexer_args *args, size_t *i)
{
    t_token         *token;
    t_token_type_flags type;
    int             offset;

    while (args->input[*i])
    {
        if (ft_isspace(args->input[*i]))
            return (get_isspace_token(args, i));
        offset = 0;
        type = get_token_type(&args->input[*i], &offset);
        printf("type: %i\n", type);
        printf("type = %s", get_token_type_name(type));
        token = get_token(args, i, offset, type);
        return (token);
    }
}

t_parse_status    lexer(t_lexer_args *args)
{
    size_t          i;
    t_token         *token;
    t_parse_status	status;
    int            okash;

    args->quote = 0;
    okash = 0;

    i = 0;
    printf("input:%s\n",args->input);
    token = get_next_token(args, &i);
    while (token)
    {
        okash++;
        if (okash > 20)
            break ;
        token = get_next_token(args, &i);
        printf("token: %s\n", token->value);
/*         status = get_parsing_error_status(token, args, &i);
		if (status != COMMAND_VALID)
			return (status); */
    }
    token = init_token(TOKEN_EOF, "", 0, 0);
/* 	return (get_parsing_error_status(token, args, &i)); */
}


int main()
{
    t_parse_status		status;
    t_lexer_args		args;
	const char *command = "( ( ( echo 'salut' ) ) && echo 'bonjour' )";

	args = init_lexer_args(command);
	status = lexer(&args);
}

// cc srcs/parsing/lexer2.c libs/libft/srcs/**/*.c  srcs/structs/token/*.c srcs/structs/lexer_args/*.c srcs/structs/dynarray/*.c -I includes -I libs/libft/include