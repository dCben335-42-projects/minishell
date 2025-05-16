/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:15 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/16 19:08:41 by abonneau         ###   ########.fr       */
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
	M_EOF							= 1 << 3,	// EOF
}	t_only_metachar;

typedef enum e_token_name
{
	TEXT						= 1 << 4,	// TEXT
	QUOTED_TEXT					= 1 << 5,	// 'TEXT'
	EXPAND						= 1 << 6,	// $VAR
	QUOTED_EXPAND				= 1 << 7,	// "$VAR"
	WILDCARD					= 1 << 8,	// WILDCARD
}	t_token_name;

typedef enum e_control_operator
{
	OP_OR						= 1 << 9,	// ||
	OP_PIPE						= 1 << 10,	// |
	OP_AND						= 1 << 11,	// &&
	OP_AMP						= 1 << 12,	// &
	OP_SEMICOL					= 1 << 13,	// ;
	OP_DB_SEMICOL				= 1 << 14,	// ;;
	OP_SEMICOL_AMP				= 1 << 15,	// ;&
	OP_DB_SEMICOL_AMP			= 1 << 16,	// ;;&
	OP_PIPE_ERR					= 1 << 17,	// |&
	OP_PARENTHESIS_OPEN			= 1 << 18,	// (
	OP_PARENTHESIS_CLOSE		= 1 << 19,	// )
}	t_control_operator;

typedef enum e_redir_operator
{
	R_IN					= 1 << 20,	// <
	R_OUT					= 1 << 21,	// >
	R_APPEND				= 1 << 22,	// >>
	R_HEREDOC				= 1 << 23,	// <<
	R_HEREDOC_TRIM			= 1 << 24,	// <<TRIM
}	t_redir_operator; 

typedef enum e_token_flag
{
	EXPECT_CONT			= 1 << 0,  // EXPECT_CONT
	ERR_LEFT_OPERAND	= 1 << 1,  // ERR_LEFT_OP
	ERR_RIGHT_OPERAND	= 1 << 2,  // ERR_RIGHT_OP
	ERR_NO_OPEN_PAREN	= 1 << 3,  // ERR_UNOPENED_PARENTHESIS
	INC_PAREN_CLOSE		= 1 << 4,  // INCREMENT_PAREN_CLOSE
	INC_PAREN_OPEN		= 1 << 5,  // INC_PAREN_OPEN
	ERR_NO_CLOSE_PAREN	= 1 << 6,  // ERR_PAREN_NOT_CLOSED
	ERR_EMPTY_PAREN		= 1 << 7,  // ERR_PAREN_EMPTY
	ERR_EMPTY_SEMI		= 1 << 8,  // ERR_SEMICOL_EMPTY
	ERR_NO_RIGHT_OPERAND	= 1 << 9,  // ERR_NO_RIGHT_OPERAND
	ERR_NO_LEFT_OPERAND	= 1 << 10, // ERR_NO_LEFT_OPERAND
	ERR_RIGHT_OPERAND_NP	= 1 << 11, // ERR_RIGHT_OPERAND_NP
}	t_token_flag;

//typedef enum e_token_type_flags
//{
//	TOKEN_SPACE					= M_SPACE,
//	TOKEN_TAB					= M_TAB,
//	TOKEN_NEWLINE				= M_NEWLINE,
//	TOKEN_TEXT					= TEXT,
//	TOKEN_EXPAND				= EXPAND,
//	TOKEN_WILDCARD				= WILDCARD,
//	TOKEN_OR					= OP_OR | ERR_LEFT_OPERAND | EXPECT_CONT,
//	TOKEN_PIPE					= OP_PIPE | ERR_LEFT_OPERAND | EXPECT_CONT,
//	TOKEN_AND					= OP_AND | ERR_LEFT_OPERAND | EXPECT_CONT,
//	TOKEN_BACKGROUND			= OP_AMP | ERR_LEFT_OPERAND | EXPECT_CONT,
//	TOKEN_SEMICOL				= OP_SEMICOL | ERR_EMPTY_SEMI,
//	TOKEN_DB_SEMICOL			= OP_DB_SEMICOL | ERR_LEFT_OPERAND,
//	TOKEN_SEMICOL_AMP			= OP_SEMICOL_AMP | ERR_LEFT_OPERAND,
//	TOKEN_DB_SEMICOL_AMP		= OP_DB_SEMICOL_AMP | ERR_LEFT_OPERAND,
//	TOKEN_PIPE_ERR				= OP_PIPE_ERR | ERR_LEFT_OPERAND | EXPECT_CONT,
//	TOKEN_PARENTHESIS_OPEN		= OP_PARENTHESIS_OPEN | EXPECT_CONT | INC_PAREN_OPEN,
//	TOKEN_PARENTHESIS_CLOSE		= OP_PARENTHESIS_CLOSE | ERR_NO_OPEN_PAREN | INC_PAREN_CLOSE | ERR_EMPTY_PAREN,
//	TOKEN_REDIR_IN				= R_IN | ERR_RIGHT_OPERAND,
//	TOKEN_REDIR_OUT				= R_OUT | ERR_RIGHT_OPERAND,
//	TOKEN_APPEND				= R_APPEND | ERR_RIGHT_OPERAND,
//	TOKEN_HEREDOC				= R_HEREDOC | ERR_RIGHT_OPERAND,
//	TOKEN_EOF					= M_EOF | ERR_NO_CLOSE_PAREN,	// EOF
//}	t_token_type_flags;

typedef struct s_token_map
{
	char				*op;
	t_uint				type;
}	t_token_map;

typedef struct s_token
{
	t_uint				type;
	t_uint				rules;
	char				*value;
}	t_token;

typedef struct s_masks
{
	t_uint	metachar;
	t_uint	text;
	t_uint	control;
	t_uint	redir;
	t_uint	paren;
	t_uint	control_extended;
}	t_masks;

typedef enum e_token_category
{
	C_METACHAR,
	C_TEXT,
	C_OPERATOR,
	C_REDIR,
	C_PAREN,
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
t_uint				get_rules(t_uint token_type);








void			*destroy_token(
					t_token *token);

const char			*get_token_type_name(
						const t_uint type);

t_uint	get_token_type(
						const char *str,
						int *offset);

t_token			*init_token(t_uint token_type, const char *start, size_t len);

int				is_control_token(
					t_token token);
int				is_text_token(
					t_token token);
int				is_redir_token(
					t_token token);
int				is_parenthesis_token(
					t_token token);
int				is_control_extended_token(
					t_token token);
int				is_cmd_token(
					t_token token);

int				is_meta_token(t_token token);

#endif