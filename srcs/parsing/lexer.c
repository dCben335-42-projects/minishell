#include "parsing.h"

static t_bool	is_command_finished(const char *input, t_token *token)
{
	if (token->type & EXPECT_CONTINUATION)
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
    t_pointer			pointer;
    t_token_type_flags	type;
    int					offset;

    while (args->input - args->start < args->input_size)
    {
        if (ft_isspace(*args->input))
            return (tokenize_whitespace(args));
        offset = 0;
        type = get_token_type(args->input, &offset);
        pointer = get_token(args, offset, type);
        return (pointer);
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
		return (COMMAND_NOT_VALID);
    status = token_parser(args, ((t_token *)pointer.pointer));
    if (status != COMMAND_VALID)
		return (status);
    if (!is_command_finished(args->input, ((t_token *)pointer.pointer)))
		return (COMMAND_NOT_FINISHED);
    return (status);
}

t_parse_status    lexer(t_lexer_args *args)
{
    t_pointer		pointer;
    t_parse_status	status;

    pointer = get_next_token(args);
    while (pointer.pointer)
    {
		status = get_parsing_error_status(args, pointer);
        if (status != COMMAND_VALID)
            return (status);
		pointer = get_next_token(args);
    }
    return (COMMAND_VALID);
}


// ( ( ( echo jojo$PATH'$GOOD'"okksa   'fjeifj'          iji*ji$HELLO"jigo/*'ffe'./?out) )&& echo $'bonjour'"salut $" )