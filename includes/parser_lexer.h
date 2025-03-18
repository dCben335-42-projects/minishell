#ifndef PARSE_LEXER_H
# define PARSE_LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "libft.h"
# include "map.h"
# include "token.h"

typedef enum e_parse_status {
	COMMAND_VALID,
	COMMAND_NOT_VALID,
	COMMAND_NOT_FINISHED,
}   t_parse_status;

typedef struct s_lexer_args {
	const char			*input;
	t_dynamic_array		tokens;
}	t_lexer_args;

typedef struct s_parser_static {
	t_bool	is_init;
	int		open_parenthesis_count;
	int		close_parenthesis_count;
}	t_parser_static;

t_parse_status	lexer(t_lexer_args *args, char **error);
void			print_tokens(t_dynamic_array *tokens);
t_parse_status	token_parser(t_lexer_args *args, char **error, t_token *token);

#endif