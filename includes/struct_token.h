/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:15 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/29 19:27:47 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TOKEN_H
# define STRUCT_TOKEN_H

# include "types.h"

# define DEBUG_MODE 					TRUE

// FLAGS
# define FLAG_BRACE_EXPANSION			FALSE	// {a,b,c}
# define FLAG_ARITHMETIC_EXPANSION		FALSE	// $((...))
# define FLAG_COMMAND_SUBSTITUTION		FALSE	// $(...)
# define FLAG_GLOBBING					TRUE	// *, ?, **
# define FLAG_GLOBBING_EXTENDED			FALSE	// [abc], [!abc], [^abc], [a-z]
# define FLAG_VAR_EXPANSION				TRUE	// $VAR
# define FLAG_VAR_EXPANSION_EXTENDED	FALSE	// ${VAR:0:1}, ${VAR#prefix}, ${VAR%suffix}

// EXPANDABLES
# define SYMBOL_VAR_EXPAND				'$'

// WILDCARDS
# define SYMBOL_GLOB_ANY				'*'
# define SYMBOL_GLOB_DIR				'**'
# define SYMBOL_GLOB_ONE				'?'
# define DELIMITER_GLOB_REGEX_CLOSE		'['
# define DELIMITER_GLOB_REGEX_OPEN		']'

// WORDS
# define DELIMITER_LITERAL_TEXT 		'\''
# define DELIMITER_EXPANDABLE_TEXT 		'"'

typedef enum e_only_metachar
{
	SPACE						= 1 << 0,	// ' '
	TAB							= 1 << 1,	// \t
	NEWLINE						= 1 << 2,	// \n
}	t_only_metachar;

typedef enum e_token_name
{
	TEXT						= 1 << 3,	// TEXT
	EXPAND						= 1 << 4,	// $VAR
	WILDCARD					= 1 << 5,	// WILDCARD
}	t_token_name;

# define E_TOKEN_NAME_MASK					56		// TEXT | EXPAND | WILDCARD

typedef enum e_control_operator
{
	OP_OR						= 1 << 6,	// ||
	OP_PIPE						= 1 << 7,	// |
	OP_AND						= 1 << 8,	// &&
	OP_AMP						= 1 << 9,	// &
	OP_SEMICOL					= 1 << 10,	// ;
	OP_DB_SEMICOL				= 1 << 11,	// ;;
	OP_SEMICOL_AMP				= 1 << 12,	// ;&
	OP_DB_SEMICOL_AMP			= 1 << 13,	// ;;&
	OP_PIPE_ERR					= 1 << 14,	// |&
	OP_PARENTHESIS_OPEN			= 1 << 15,	// (
	OP_PARENTHESIS_CLOSE		= 1 << 16,	// )
}	t_control_operator;

# define E_CONTROL_OPERATOR_MASK			32704	// WITHOUT PARENTHESIS
# define E_CONTROL_OPERATOR_EXTENDED_MASK	131008	// WITH PARENTHESIS
# define E_PARENTHESIS_MASK					98304	// PARENTHESIS ONLY

typedef enum e_redir_operator
{
	REDIR_IN					= 1 << 17,	// <
	REDIR_OUT					= 1 << 18,	// >
	REDIR_APPEND				= 1 << 19,	// >>
	REDIR_HEREDOC				= 1 << 20,	// <<
}	t_redir_operator; 

# define E_REDIR_OPERATOR_MASK 1966080

typedef enum e_token_flag
{
	EXPECT_CONTINUATION			= 1 << 23,
	ERR_MISSING_LEFT_OPERAND	= 1 << 24,
	ERR_MISSING_RIGHT_OPERAND	= 1 << 25,
	ERR_UNOPENED_PARENTHESIS	= 1 << 26,
	INCREMENT_PAREN_CLOSE		= 1 << 27,
	INCREMENT_PAREN_OPEN		= 1 << 28,
	ERR_PAREN_NOT_CLOSED		= 1 << 29,
}	t_token_flag;

typedef enum e_token_type_flags
{
	TOKEN_SPACE					= SPACE,
	TOKEN_TAB					= TAB,
	TOKEN_NEWLINE				= NEWLINE,
	TOKEN_TEXT					= TEXT,
	TOKEN_EXPAND				= EXPAND,
	TOKEN_WILDCARD				= WILDCARD,
	TOKEN_OR					= OP_OR | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	TOKEN_BACKGROUND			= OP_AMP | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	TOKEN_AND					= OP_AND | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	TOKEN_SEMICOL				= OP_SEMICOL | ERR_MISSING_LEFT_OPERAND,
	TOKEN_DB_SEMICOL			= OP_DB_SEMICOL | ERR_MISSING_LEFT_OPERAND,
	TOKEN_SEMICOL_AMP			= OP_SEMICOL_AMP | ERR_MISSING_LEFT_OPERAND,
	TOKEN_DB_SEMICOL_AMP		= OP_DB_SEMICOL_AMP | ERR_MISSING_LEFT_OPERAND,
	TOKEN_PIPE					= OP_PIPE | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	TOKEN_PIPE_ERR				= OP_PIPE_ERR | ERR_MISSING_LEFT_OPERAND | EXPECT_CONTINUATION,
	TOKEN_PARENTHESIS_OPEN		= OP_PARENTHESIS_OPEN | EXPECT_CONTINUATION | INCREMENT_PAREN_OPEN,
	TOKEN_PARENTHESIS_CLOSE		= OP_PARENTHESIS_CLOSE | ERR_MISSING_LEFT_OPERAND | ERR_UNOPENED_PARENTHESIS | INCREMENT_PAREN_CLOSE,
	TOKEN_REDIR_IN				= REDIR_IN | ERR_MISSING_LEFT_OPERAND,
	TOKEN_REDIR_OUT				= REDIR_OUT | ERR_MISSING_LEFT_OPERAND,
	TOKEN_APPEND				= REDIR_APPEND | ERR_MISSING_LEFT_OPERAND,
	TOKEN_HEREDOC				= REDIR_HEREDOC | ERR_MISSING_LEFT_OPERAND,
	TOKEN_EOF					= 1 << 21 | ERR_PAREN_NOT_CLOSED,	// EOF
}	t_token_type_flags;

typedef struct s_token_map
{
	char				*op;
	t_token_type_flags	token;
}	t_token_map;

typedef struct s_token
{
	t_token_type_flags	type;
	char				*value;
}	t_token;

void			*destroy_token(
					t_token *token);

const char			*get_token_type_name(
						const t_token_type_flags type);

t_token_type_flags	get_token_type(
						const char *str,
						int *offset);

t_token			*init_token_p(
					int token_type,
					const char *start,
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