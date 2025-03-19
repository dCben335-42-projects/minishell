#ifndef PARSE_LEXER_H
# define PARSE_LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "libft.h"
# include "map.h"
# include "token.h"
# include "lexer_args.h"

typedef enum e_parse_status
{
	COMMAND_VALID,
	COMMAND_NOT_VALID,
	COMMAND_NOT_FINISHED,
}   t_parse_status;

t_parse_status	lexer(t_lexer_args *args);
void			print_tokens(t_dynamic_array *tokens);
t_parse_status	token_parser(t_lexer_args *args, t_token *token);

#endif