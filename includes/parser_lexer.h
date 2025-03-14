#ifndef PARSE_LEXER_H
# define PARSE_LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "libft.h"
# include "map.h"

# define MAX_TOKENS 20
# define OP_TABLE_SIZE 9
# define OP_TABLE_MAX_BRANCH 3

typedef enum e_token_type {
    TOKEN_TEXT,             // Texte sans guillemets                    => tout est interpreté
    TOKEN_VAR_TEXT,         // Texte entre guillemets doubles           => les variables sont interpretées (wildcard pas interprété si pas dans variable)
    TOKEN_LITERAL_TEXT,     // Texte entre guillemets simples           => rien n'est interpreté
    TOKEN_PIPE,        // |
    TOKEN_AND,         // &&
    TOKEN_OR,          // ||
    TOKEN_SEMICOL,     // ;
    TOKEN_REDIR_IN,    // <
    TOKEN_REDIR_OUT,   // >
    TOKEN_APPEND,      // >>
    TOKEN_BACKGROUND,  // &
    TOKEN_PIPE_ERR,    // |&
    TOKEN_QUOTE,       // '
    TOKEN_DQUOTE,      // "
    TOKEN_OPEN_BRACKET,     // (
    TOKEN_CLOSE_BRACKET,    // )
    TOKEN_EOF          // Fin de commande
} t_token_type;

typedef enum e_parse_status {
    COMMAND_VALID,
    COMMAND_NOT_VALID,
    COMMAND_NOT_FINISHED,
}   t_parse_status;

typedef struct s_token_name {
    char *name;
} t_token_name;

typedef struct s_token{
    t_token_type type;
    char *value;
} t_token;

typedef struct {
    char next_char;
    t_token_type type;
} transition;

typedef struct {
    char key;
    transition transitions[OP_TABLE_MAX_BRANCH];
} operator_table;

typedef struct s_lexer_args {
	const char          *input;
	t_dynamic_array     *tokens;
    int			        token_number_max;
	int			        token_count;
} t_lexer_args;

typedef struct s_parser_static {
	t_bool	is_init;
	int		open_bracket_count;
	int		close_bracket_count;
} t_parser_static;

t_parse_status	lexer(t_lexer_args *args, char **error);
void            print_tokens(t_dynamic_array *tokens, int count);
t_parse_status  token_parser(t_lexer_args *args, char **error, t_token token);

#endif