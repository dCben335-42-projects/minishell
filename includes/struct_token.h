/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:15 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/05 22:02:58 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TOKEN_H
# define STRUCT_TOKEN_H

# include "types.h"
# include "struct_dynarray.h"

/**
 *	@brief Enumeration of token types.
 *
 *	@note This enumeration is used to define the different types of tokens
 *	that can be encountered during parsing.
 *
 *	@note Each token type is represented by a bit flag, allowing for
 *	bitwise operations to check for specific token types.
 *
*/
typedef enum e_token_type
{
	M_EOF						= 1 << 0,
	M_SPACE						= 1 << 1,
	TEXT						= 1 << 2,
	QUOTED_TEXT					= 1 << 3,
	EXPAND						= 1 << 4,
	QUOTED_EXPAND				= 1 << 5,
	WILDCARD					= 1 << 6,
	OP_OR						= 1 << 7,
	OP_PIPE						= 1 << 8,
	OP_AND						= 1 << 9,
	OP_SEMICOL					= 1 << 10,
	OP_PARENTHESIS_OPEN			= 1 << 11,
	OP_PARENTHESIS_CLOSE		= 1 << 12,
	R_IN						= 1 << 13,
	R_OUT						= 1 << 14,
	R_APPEND					= 1 << 15,
	R_HEREDOC					= 1 << 16,
	R_HEREDOC_TRIM				= 1 << 17,
}	t_token_type;

/**
 * @brief Enumeration of token flags.
 * 
 * @note This enumeration is used to define different flags
 * that can be associated with tokens during parsing.
 * 
 * @param EXPECT_CONT Flag indicating that a continuation is expected.
 * @param ERR_LEFT_OPERAND Flag indicating an error with the left operand.
 * @param ERR_RIGHT_OPERAND Flag indicating an error with the right operand.
 * @param ERR_NO_OPEN_PAREN Flag indicating no open parenthesis found.
 * @param INC_PAREN_CLOSE Flag indicating an incorrect closing parenthesis.
 * @param INC_PAREN_OPEN Flag indicating an incorrect opening parenthesis.
 * @param ERR_NO_CLOSE_PAREN Flag indicating no closing parenthesis found.
 * @param ERR_EMPTY_PAREN Flag indicating an empty parenthesis.
 * @param ERR_EMPTY_SEMI Flag indicating an empty semicolon.
 * @param ERR_NO_RIGHT_OPERAND Flag indicating no right operand found.
 * @param ERR_NO_LEFT_OPERAND Flag indicating no left operand found.
 * @param ERR_RIGHT_OPERAND_NP Flag indicating a right operand not found.
*/
typedef enum e_token_flag
{
	EXPECT_CONT					= 1 << 0,
	ERR_LEFT_OPERAND			= 1 << 1,
	ERR_RIGHT_OPERAND			= 1 << 2,
	ERR_NO_OPEN_PAREN			= 1 << 3,
	INC_PAREN_CLOSE				= 1 << 4,
	INC_PAREN_OPEN				= 1 << 5,
	ERR_NO_CLOSE_PAREN			= 1 << 6,
	ERR_EMPTY_PAREN				= 1 << 7,
	ERR_EMPTY_SEMI				= 1 << 8,
	ERR_NO_RIGHT_OPERAND		= 1 << 9,
	ERR_NO_LEFT_OPERAND			= 1 << 10,
	ERR_RIGHT_OPERAND_NP		= 1 << 11,
}	t_token_flag;

typedef struct s_token
{
	t_token_type		type;
	t_uint				rules;
	char				*value;
}	t_token;

t_token			*init_token(
					t_token_type token_type,
					const char *start,
					size_t len);
void			*destroy_token(t_token *token);

/**
 * @brief Structure that maps operators to their token types.
 * 
 * @note This structure is used to identify the type of token
 * based on the operator string.
 * 
 * @param op The operator string.
 * @param type The token type associated with the operator.
 * 
 * @note The operator string is used to match the input string
*/
typedef struct s_token_map
{
	const char			*op;
	t_token_type		type;
}	t_token_map;

t_token_type	get_token_type(const char *str, int *op_len);

/**
 * @brief Structure that holds the token type and its name.
 * 
 * @param type The token type.
 * @param name The name of the token type.
 * 
 * @note This structure is on ly used for printing purposes
 * and is not used in the parsing process.
*/
typedef struct s_token_print
{
	t_uint		type;
	const char	*name;
}	t_token_print;

void			print_tokens(t_dynarray *tokens);

/**
 * @brief Structure that holds masks for different token types.
 * 
 * @param metachar Mask for metacharacter tokens.
 * @param text Mask for text tokens.
 * @param control Mask for control tokens.
 * @param redir Mask for redirection tokens.
 * @param paren Mask for parenthesis tokens.
 * @param control_extended Mask for extended control tokens.
 * 
 * @note The masks are then used to check 
 * if a token belongs to a specific category
*/
typedef struct s_masks
{
	t_uint	metachar;
	t_uint	text;
	t_uint	control;
	t_uint	redir;
	t_uint	paren;
	t_uint	control_extended;
}	t_masks;

/**
 * @brief Enumeration of token categories.
 * 
 * @note This enumeration is used to categorize tokens
 * based on their type and behavior during parsing.
 * 
 * @param C_METACHAR Represents metacharacter tokens.
 * @param C_TEXT Represents text tokens.
 * @param C_OPERATOR Represents operator tokens.
 * @param C_REDIR Represents redirection tokens.
 * @param C_PAREN Represents parenthesis tokens.
*/
typedef enum e_token_category
{
	C_METACHAR,
	C_TEXT,
	C_OPERATOR,
	C_REDIR,
	C_PAREN,
}	t_token_category;

/**
 * @brief Structure that maps token types to their rules and categories.
 * 
 * @param type The token type.
 * @param rules The rules associated with the token type.
 * @param category The category of the token type.
 * 
 * @note This structure is used to define the behavior of each token type
 * during parsing.
*/
typedef struct s_token_map_rules
{
	t_token_type		type;
	t_uint				rules;
	t_token_category	category;
}	t_token_map_rules;

t_masks			*get_masks(void);
t_uint			get_token_rules(t_token_type token_type);

int				is_control_token(t_token token);
int				is_text_token(t_token token);
int				is_redir_token(t_token token);
int				is_parenthesis_token(t_token token);
int				is_control_extended_token(t_token token);
int				is_cmd_token(t_token token);
int				is_meta_token(t_token token);

#endif