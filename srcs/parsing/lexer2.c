#include "parsing.h"

t_token	*handler_token_text(size_t *i, t_lexer_args *args)
{
	size_t				start_i;
    t_token_type_flags	current_type;

	start_i = *i;
	current_type = TOKEN_TEXT;
	while (args->input[*i] && !ft_isspace(args->input[*i])
		&& get_token_type(&args->input[*i], 0) == TOKEN_TEXT)
    {
        if (args->input[*i] == DQUOTE)
        {
            if (args->quote == 0)
			{
                args->quote = DQUOTE;
				if (*i - start_i > 0)
				{
					(*i)++;
					return (init_token(current_type, args->input, start_i, *i - start_i - 1));
				}
				if (*i - start_i == 0)
					start_i++;
			}
            else if (args->quote == DQUOTE)
			{
                args->quote = 0;
				if (*i - start_i > 0)
				{
					(*i)++;
					return (init_token(current_type, args->input, start_i, *i - start_i - 1));
				}
			}
        }
        if (args->input[*i] == QUOTE)
        {
            if (args->quote == 0)
			{
                args->quote = QUOTE;
				if (*i - start_i > 0)
				{
					(*i)++;
					return (init_token(current_type, args->input, start_i, *i - start_i - 1));
				}
				if (*i - start_i == 0)
					start_i++;
			}
            else if (args->quote == QUOTE)
			{
                args->quote = 0;
				if (*i - start_i > 0)
				{
					(*i)++;
					return (init_token(current_type, args->input, start_i, *i - start_i - 1));
				}
			}
        }
        if (args->input[*i] == EXPAND_EXPR && (args->quote == 0 || args->quote == DQUOTE))
        {
            if (*i - start_i > 0)
                return (init_token(current_type, args->input, start_i, *i - start_i));
            else
				current_type = TOKEN_EXPAND;
        }
		// if (args->input[*i] == WILDCARD_EXPR && args->quote == 0)
        // {
        //     if (*i - start_i > 0)
        //         return (init_token(current_type, args->input, start_i, *i - start_i));
        //     else
		// 		current_type = WILDCARD_EXPR;
        // }
		(*i)++;
    }
	return (init_token(current_type, args->input, start_i, *i - start_i));
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

t_token	*handler_token_operator(t_lexer_args *args,
	size_t *i, int offset, t_token_type_flags type)
{
	t_token	*token;

	token = init_token(type, args->input, *i, offset);
	*i += offset;
	return (token);
}

static t_token	*get_token(
	t_lexer_args *args,
	size_t *i,
	int offset,
	t_token_type_flags type
)
{
	if (type == TOKEN_TEXT)
		return (handler_token_text(i, args));
    return (handler_token_operator(args, i, offset, type));
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
    // printf("type = %s; %-12s\n", get_token_type_name(token->type) , token->value);
    printf("%-40s %-40s\n", get_token_type_name(token->type), token->value);

    while (token)
    {
        okash++;
        if (okash > 40)
            break ;
        token = get_next_token(args, &i);
        if (!token)
            break ;
        // printf("type = %s; %s\n", get_token_type_name(token->type) , token->value);
        printf("%-40s %-40s\n", get_token_type_name(token->type), token->value);
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
	// const char *command = "( ( ( echo 'salut' ) ) && echo 'bonjour' )";
    const char *command = "( ( ( echo jojo$PATH'$GOOD'\"ijiji$HELLO\" ) ) && echo 'bonjour' )";

	args = init_lexer_args(command);
	status = lexer(&args);
}

// cc srcs/parsing/lexer2.c libs/libft/srcs/**/*.c  srcs/structs/token/*.c srcs/structs/lexer_args/*.c srcs/structs/dynarray/*.c -I includes -I libs/libft/include