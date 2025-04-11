#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>
# include "types.h"

typedef enum e_token_type
{
	TOKEN_TEXT,				// [1] def=TEXT
	TOKEN_VAR_TEXT,			// [2] def="TEXT"
	TOKEN_LITERAL_TEXT,		// [3] def='TEXT'
	TOKEN_PIPE,				// [4] def=|
	TOKEN_AND,				// [5] def=&&
	TOKEN_OR,				// [6] def=||
	TOKEN_SEMICOL,			// [7] def=;
	TOKEN_REDIR_IN,			// [8] def=<
	TOKEN_REDIR_OUT,		// [9] def=>
	TOKEN_APPEND,			// [10] def=>>
	TOKEN_HEREDOC,			// [11] def=<<
	TOKEN_BACKGROUND,		// [12] def=&
	TOKEN_PIPE_ERR,			// [13] def=|&
	TOKEN_QUOTE,			// [14] def='
	TOKEN_DQUOTE,			// [15] def="
	TOKEN_OPEN_BRACKET,		// [16] def=(
	TOKEN_CLOSE_BRACKET,	// [17] def=)
	TOKEN_SPACE,			// [18] def=WHITESPACE
	TOKEN_UNKNOWN,			// [19] def=unknown
	TOKEN_EOF,				//	[20] def=EOF
}	t_token_type;

typedef struct s_token_map
{
	char			*op;
	t_token_type	token;
}	t_token_map;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

void			*destroy_token(
					t_token *token);

const char		*get_token_type_name(
					const t_token_type type);

t_token_type	get_token_type(
					const char *str,
					int *offset);

t_token			*init_token(int token_type,
					const char *value,
					t_uint start,
					size_t len);

int				is_operator_token(
					t_token token);
int				is_text_token(
					t_token token);
int				is_redir_token(
					t_token token);
int				is_parenthesis_token(
					t_token token);

#endif