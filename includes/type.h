#ifndef TYPE_H
# define TYPE_H

//typedef enum e_metacharacter
//{
//	CMD_SPACE = ' ',
//}	t_metacharacter;

//typedef enum e_token_type
//{
//	WORD,
//	METACHARACTER,
//}	t_token_type;


//typedef enum e_control_operator
//{
//	SEMICOLON,
//	AND,
//	OR,
//	PIPE,
//	PIPE_WITH_STDERR,
//	SUBSHELL,
//	BRACE_GROUP,
//	REDIRECTION,
//}	t_control_operator;

typedef enum e_token_type {
	TOKEN_SPACE,   // Espace
    TOKEN_WORD,    // Mot ou commande
    TOKEN_PIPE,    // |
    TOKEN_AND,     // &&
    TOKEN_OR,      // ||
    TOKEN_SEMICOL, // ;
    TOKEN_REDIR_IN,  // <
    TOKEN_REDIR_OUT, // >
    TOKEN_APPEND,  // >>
    TOKEN_BACKGROUND, // &
    TOKEN_EOF      // Fin de commande
} t_token_type;

typedef enum e_bool {
	FALSE,
	TRUE
} t_bool;

#endif