#ifndef LEXER_ARGS_H
# define LEXER_ARGS_H

#include "map.h"

typedef struct s_bracket
{
	size_t		open;
	size_t		close;
}	t_bracket;

typedef struct s_lexer_args
{
	const char			*input;
	char				*error;
	t_dynamic_array		tokens;
	t_bracket			parenthesis;
	t_bracket			bracket;
}	t_lexer_args;

t_lexer_args	init_lexer_args(const char *input);
void			*destroy_lexer_args(t_lexer_args *args);

#endif