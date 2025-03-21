#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

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
	TOKEN_UNKNOWN,     // Token inconnu
	TOKEN_EOF          // Fin de commande
}	t_token_type;

typedef struct s_token_map {
	char 			*op;
	t_token_type	token;
}	t_token_map;

typedef struct s_token {
	t_token_type type;
	char *value;
}	t_token;

void			*destroy_token(t_token *token);
const char		*get_token_type_name(const t_token_type type);
t_token_type    get_token_type(const char *str, int *offset);
t_token			*init_token(int token_type, const char *value, unsigned int start, size_t len);
int				is_operator_token(t_token token);

#endif