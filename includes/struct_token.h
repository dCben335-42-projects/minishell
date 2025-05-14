/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:15 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/14 19:59:42 by abonneau         ###   ########.fr       */
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
# define SYMBOL_GLOB_DIR				"**"
# define SYMBOL_GLOB_ONE				'?'
# define DELIMITER_GLOB_REGEX_CLOSE		'['
# define DELIMITER_GLOB_REGEX_OPEN		']'

// WORDS
# define DELIMITER_LITERAL_TEXT 		'\''
# define DELIMITER_EXPANDABLE_TEXT 		'"'

typedef enum e_only_metachar
{
	M_SPACE							= 1 << 0,	// ' '
	M_TAB							= 1 << 1,	// \t
	M_NEWLINE						= 1 << 2,	// \n
	M_EOF							= 1 << 21,	// EOF
}	t_only_metachar;

typedef enum e_token_name
{
	TEXT						= 1 << 3,	// TEXT
	QUOTED_TEXT					= 1 << 22,	// 'TEXT'
	EXPAND						= 1 << 4,	// $VAR
	QUOTED_EXPAND				= 1 << 23,	// "$VAR"
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
	R_IN					= 1 << 17,	// <
	R_OUT					= 1 << 18,	// >
	R_APPEND				= 1 << 19,	// >>
	R_HEREDOC				= 1 << 20,	// <<
	R_HEREDOC_TRIM			= 1 << 24,	// <<TRIM
}	t_redir_operator; 

# define E_REDIR_OPERATOR_MASK 1966080

typedef enum e_token_flag
{
	EXPECT_CONT			= 1 << 23,  // EXPECT_CONT
	ERR_LEFT_OPERAND	= 1 << 24,  // ERR_LEFT_OP
	ERR_RIGHT_OPERAND	= 1 << 25,  // ERR_RIGHT_OP
	ERR_NO_OPEN_PAREN	= 1 << 26,  // ERR_UNOPENED_PARENTHESIS
	INC_PAREN_CLOSE		= 1 << 27,  // INCREMENT_PAREN_CLOSE
	INC_PAREN_OPEN		= 1 << 28,  // INC_PAREN_OPEN
	ERR_NO_CLOSE_PAREN	= 1 << 29,  // ERR_PAREN_NOT_CLOSED
	ERR_EMPTY_PAREN		= 1 << 30,  // ERR_PAREN_EMPTY
	ERR_EMPTY_SEMI		= 1 << 31,  // ERR_SEMICOL_EMPTY
}	t_token_flag;

typedef enum e_token_type_flags
{
	TOKEN_SPACE					= M_SPACE,
	TOKEN_TAB					= M_TAB,
	TOKEN_NEWLINE				= M_NEWLINE,
	TOKEN_TEXT					= TEXT,
	TOKEN_EXPAND				= EXPAND,
	TOKEN_WILDCARD				= WILDCARD,
	TOKEN_OR					= OP_OR | ERR_LEFT_OPERAND | EXPECT_CONT,
	TOKEN_PIPE					= OP_PIPE | ERR_LEFT_OPERAND | EXPECT_CONT,
	TOKEN_AND					= OP_AND | ERR_LEFT_OPERAND | EXPECT_CONT,
	TOKEN_BACKGROUND			= OP_AMP | ERR_LEFT_OPERAND | EXPECT_CONT,
	TOKEN_SEMICOL				= OP_SEMICOL | ERR_EMPTY_SEMI,
	TOKEN_DB_SEMICOL			= OP_DB_SEMICOL | ERR_LEFT_OPERAND,
	TOKEN_SEMICOL_AMP			= OP_SEMICOL_AMP | ERR_LEFT_OPERAND,
	TOKEN_DB_SEMICOL_AMP		= OP_DB_SEMICOL_AMP | ERR_LEFT_OPERAND,
	TOKEN_PIPE_ERR				= OP_PIPE_ERR | ERR_LEFT_OPERAND | EXPECT_CONT,
	TOKEN_PARENTHESIS_OPEN		= OP_PARENTHESIS_OPEN | EXPECT_CONT | INC_PAREN_OPEN,
	TOKEN_PARENTHESIS_CLOSE		= OP_PARENTHESIS_CLOSE | ERR_NO_OPEN_PAREN | INC_PAREN_CLOSE | ERR_EMPTY_PAREN,
	TOKEN_REDIR_IN				= R_IN | ERR_RIGHT_OPERAND,
	TOKEN_REDIR_OUT				= R_OUT | ERR_RIGHT_OPERAND,
	TOKEN_APPEND				= R_APPEND | ERR_RIGHT_OPERAND,
	TOKEN_HEREDOC				= R_HEREDOC | ERR_RIGHT_OPERAND,
	TOKEN_EOF					= M_EOF | ERR_NO_CLOSE_PAREN,	// EOF
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

typedef struct s_masks
{
	t_uint	metachar;
	t_uint	name;
	t_uint	control;
	t_uint	redir;
	t_uint	paren;
	t_uint	extended;
}	t_masks;

typedef enum e_token_category
{
	C_METACHAR,
	C_TEXT,
	C_OPERATOR,
	C_REDIR,
	C_PARENTHESES,
}	t_token_category;

typedef struct s_token_map_rules
{
	t_uint				type;
	t_uint				rules;
	t_token_category	category;
}	t_token_map_rules;

typedef struct s_lexer_token_def
{
	t_masks					masks;
	const t_token_map_rules	*map;
}	t_lexer_token_def;

t_lexer_token_def	*get_lexer_token_def(void);









void			*destroy_token(
					t_token *token);

const char			*get_token_type_name(
						const t_token_type_flags type);

t_token_type_flags	get_token_type(
						const char *str,
						int *offset);

t_token			*init_token(
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
int				is_operator_ext_token(
					t_token token);
int				is_cmd_token(
					t_token token);

#endif