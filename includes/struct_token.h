/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:15 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 20:15:13 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TOKEN_H
# define STRUCT_TOKEN_H

# include "types.h"

/* typedef enum e_token_type
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
	TOKEN_EOF,				// [20] def=EOF
}	t_token_type; */

typedef enum e_only_metachar
{
	SPACE						= 1 << 0,	// ' '
	TAB							= 1 << 1,	// \t
	NEWLINE						= 1 << 2,	// \n
}	t_only_metachar;

typedef enum e_control_operator
{
	OP_OR						= 1 << 3,	// ||
	OP_PIPE						= 1 << 4,	// |
	OP_AND						= 1 << 5,	// &&
	OP_AMP						= 1 << 6,	// &
	OP_SEMICOL					= 1 << 7,	// ;
	OP_DB_SEMICOL				= 1 << 8,	// ;;
	OP_SEMICOL_AMP				= 1 << 9,	// ;&
	OP_DB_SEMICOL_AMP			= 1 << 10,	// ;;&
	OP_PIPE_ERR					= 1 << 11,	// |&
	OP_PARENTHESIS_OPEN			= 1 << 12,	// (
	OP_PARENTHESIS_CLOSE		= 1 << 13,	// )
}	t_control_operator;

typedef enum e_redir_operator
{
	REDIR_IN					= 1 << 14,	// <
	REDIR_OUT					= 1 << 15,	// >
	REDIR_APPEND				= 1 << 16,	// >>
	REDIR_HEREDOC				= 1 << 17,	// <<
}	t_redir_operator;

typedef enum e_token_name
{
	TEXT						= 1 << 18,	// TEXT
	EXPAND						= 1 << 19,	// $VAR
	WILDCARD					= 1 << 20,	// WILDCARD
}	t_token_name;

typedef enum e_token_flag
{
	EXPECT_CONTINUATION			= 1 << 21,
	ERR_MISSING_LEFT_OPERAND	= 1 << 22,
	ERR_MISSING_RIGHT_OPERAND	= 1 << 23,
	ERR_UNOPENED_PARENTHESIS	= 1 << 24,
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
	TOKEN_PARENTHESIS_OPEN		= OP_PARENTHESIS_OPEN | ERR_MISSING_LEFT_OPERAND,
	TOKEN_PARENTHESIS_CLOSE		= OP_PARENTHESIS_CLOSE | ERR_MISSING_LEFT_OPERAND,
	TOKEN_REDIR_IN				= REDIR_IN | ERR_MISSING_LEFT_OPERAND,
	TOKEN_REDIR_OUT				= REDIR_OUT | ERR_MISSING_LEFT_OPERAND,
	TOKEN_APPEND				= REDIR_APPEND | ERR_MISSING_LEFT_OPERAND,
	TOKEN_HEREDOC				= REDIR_HEREDOC | ERR_MISSING_LEFT_OPERAND,
	TOKEN_UNKNOWN				= 1 << 25,	// unknown
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

/* typedef struct s_token_map
{
	char			*op;
	t_token_type	token;
}	t_token_map;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

t_token			*init_token(int token_type,
					const char *value,
					t_uint start,
					size_t len);

void			*destroy_token(t_token *token);
const char		*get_token_type_name(const t_token_type type);
t_token_type	get_token_type(const char *str, int *offset);

t_bool			is_operator_token(t_token token);
t_bool			is_text_token(t_token token);
t_bool			is_redir_token(t_token token);
t_bool			is_parenthesis_token(t_token token);
 */
#endif