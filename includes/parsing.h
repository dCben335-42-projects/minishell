/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:45:18 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/28 16:22:21 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include "libft.h"
# include "struct_dynarray.h"
# include "struct_token.h"
# include "struct_lexer_args.h"
# include "struct_pointer.h"

typedef enum e_parse_status
{
	COMMAND_VALID,
	COMMAND_NOT_VALID,
	COMMAND_NOT_FINISHED,
	MALLOC_ERROR,
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
t_pointer		handler_token_quote(t_lexer_args *args,
					char *start_i,
					t_token_type_flags *current_type,
					const char quote);


/**
 * @brief Function to manage text tokens
 * @param i: index of the input string
 * @param args: lexer arguments
 */
t_pointer		handler_token_text(t_lexer_args *args);

/**
 * @brief Function to manage operator tokens
 * @param args: lexer arguments
 * @param i: index of the input string
 * @param offset: offset of the token
 * @param type: token type
 * @return the token
 */
t_pointer		handler_token_operator(t_lexer_args *args,
					int offset, t_token_type_flags type);

t_pointer		tokenize_enclosures(
					t_lexer_args *args, 
					char **start_i, 
					t_token_type_flags *current_type);
					
t_pointer		tokenize_operator(
					t_lexer_args *args,
					int offset,
					t_token_type_flags type);

t_pointer		tokenize_whitespace(t_lexer_args *args);

t_pointer		tokenize_word(t_lexer_args *args);

t_pointer		get_token(
					t_lexer_args *args,
					int offset,
					t_token_type_flags type);

t_bool	is_an_expand(t_lexer_args * args);
t_bool	is_a_wildcard(t_lexer_args * args, t_token_type_flags *current_type);

#endif