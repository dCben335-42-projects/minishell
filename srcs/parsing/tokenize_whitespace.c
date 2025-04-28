#include "parsing.h"

t_pointer	tokenize_whitespace(t_lexer_args *args)
{
    while (ft_isspace(*args->input))
        args->input++;
    return (init_pointer(init_token_p(TOKEN_SPACE, 0, 0), TRUE, FALSE));
}