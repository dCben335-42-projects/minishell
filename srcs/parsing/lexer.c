#include "parsing.h"

static t_bool	is_command_finished(const char *input, t_token *token, t_lexer_args *args)
{
	if (token->type & EXPECT_CONTINUATION || args->parenthesis.open > args->parenthesis.close)
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
    int	                                                                        offset;

    while (*args->input)
    {
        if (ft_isspace(*args->input))
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
		pointer = get_next_token(args);
    }
    pointer2 = init_pointer(init_token(TOKEN_EOF, 0, 0), TRUE, FALSE);
    if (((t_token *)pointer2.pointer) == NULL)
        return (MALLOC_ERROR);
    push(&args->tokens, ((t_token *)pointer2.pointer));
    return (COMMAND_VALID);
}


// ( ( ( echo jojo$PATH'$GOOD'"okksa   'fjeifj'          iji*ji$HELLO"jigo/*'ffe'./?out) )&& echo $'bonjour'"salut $" )
// bash: erreur de syntaxe : fin de fichier prématurée