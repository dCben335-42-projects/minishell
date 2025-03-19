#ifndef PARSE_LEXER_H
# define PARSE_LEXER_H

# include <stdio.h>
# include "libft.h"
# include "dynamic_array.h"
# include "token.h"
# include "lexer_args.h"

typedef enum e_parse_status
{
	COMMAND_VALID,
	COMMAND_NOT_VALID,
	COMMAND_NOT_FINISHED,
}	t_parse_status;

/**
 * @brief Analyzes the input to determine if it follows a valid command format.
 *
 * This function processes the input string using lexical analysis 
 * to extract tokens and validate the command structure.
 *
 * @param args The lexer arguments containing the input string and 
 * parsing context.
 * @return The status of the command parsing:
 * - `COMMAND_VALID` if the command is correctly formatted.
 * - `COMMAND_NOT_VALID` if the command contains syntax errors.
 * - `COMMAND_NOT_FINISHED` if the command is incomplete
 * (e.g., missing closing quotes).
 */
t_parse_status	lexer(t_lexer_args *args);

/**
 * @brief Function to print tokens
 * @param tokens: tokens to print
 * @return void
 */
void			print_tokens(t_dynamic_array *tokens);

/**
 * @brief Function to check whether the command is still in a valid
 * format after the new token has been added.
 * @param input: input string
 * @param offset: offset of the token
 * @return the type of the token
 */
t_parse_status	token_parser(t_lexer_args *args, t_token *token);

/**
 * @brief Function to manage tokens between quotation marks
 * @param i: index of the input string
 * @param args: lexer arguments
 * @param type: token type
 * @return the token
 */
t_token			*handler_token_quote(size_t *i, t_lexer_args *args,
					t_token_type type);

/**
 * @brief Function to manage text tokens
 * @param i: index of the input string
 * @param args: lexer arguments
 */
t_token			*handler_token_text(size_t *i, t_lexer_args *args);

/**
 * @brief Function to manage operator tokens
 * @param args: lexer arguments
 * @param i: index of the input string
 * @param offset: offset of the token
 * @param type: token type
 * @return the token
 */
t_token			*handler_token_operator(t_lexer_args *args,
					size_t *i, int offset, t_token_type type);

#endif