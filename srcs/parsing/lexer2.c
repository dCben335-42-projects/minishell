#include "parsing.h"

t_pointer	get_next_token(t_lexer_args *args)
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
	t_pointer pointer
)
{
	if (pointer.is_malloc && ((t_token *)pointer.pointer) == NULL)
		return (COMMAND_NOT_VALID);
}



t_parse_status    lexer(t_lexer_args *args)
{
    t_pointer		pointer;
    t_parse_status	status;

    pointer = get_next_token(args);
    while (pointer.pointer)
    {
		if (!get_parsing_error_status(pointer))
			return (status);
        printf("%-40s %-40s\n", get_token_type_name(((t_token *)pointer.pointer)->type), ((t_token *)pointer.pointer)->value);
		pointer = get_next_token(args);
    }
}











int main()
{
    t_parse_status		status;
    t_lexer_args		args;
	// const char *command = "( ( ( echo 'salut' ) ) && echo 'bonjour' )";
    const char *command = "( ( ( echo jojo$PATH'$GOOD'\"okksa   'fjeifj'          iji*ji$HELLO\"jigo/*'ffe') ) && echo $'bonjour'\"salut $\" )";

    printf("input:%s\n", command);
	args = init_lexer_args(command);
	status = lexer(&args);
}

// cc srcs/parsing/lexer2.c srcs/parsing/tokenize_*.c srcs/parsing/get_token.c libs/libft/srcs/**/*.c  srcs/structs/token/*.c srcs/structs/lexer_args/*.c srcs/structs/dynarray/*.c srcs/structs/pointer/*.c -I includes -I libs/libft/includes
