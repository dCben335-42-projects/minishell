/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:45:18 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/29 20:20:15 by bcabocel         ###   ########.fr       */
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

t_parse_status	lexer(t_lexer_args *args);
t_parse_status	get_parsing_error_status(t_lexer_args *args, t_ptr pointer);

t_ptr		tokenize_enclosures(t_lexer_args *args, char **start_i, t_token_type *current_type);
t_ptr		tokenize_operator(t_lexer_args *args, int offset, t_token_type type);
t_ptr		tokenize_whitespace(t_lexer_args *args);
t_ptr		tokenize_word(t_lexer_args *args);
t_ptr		tokenize_wildcard(t_lexer_args *args, t_token_type *current_type);
t_ptr		tokenize_expand(t_lexer_args *args, char **start_i, t_token_type *current_type);

t_ptr		get_token(t_lexer_args *args, int offset,t_token_type type);
t_bool		get_prev_token(t_lexer_args *args, t_token **prev_token);

t_token_type	quoted_wrapper(t_lexer_args *args, t_token_type *current_type);
t_ptr			transform_heredoc(t_lexer_args *args, t_token *token, t_bool is_expandable, t_token_type type);

typedef struct s_rules_map
{
	t_token_flag	key;
	t_parse_status	(*f)(t_lexer_args *args, t_token *token);
}	t_rules_map;

t_parse_status	token_parser(t_lexer_args *args, t_token *token);
t_parse_status	check_all_rules(t_lexer_args *args, t_token *token);

t_parse_status	increment_parenthesis_open(t_lexer_args *args, t_token *token);
t_parse_status	increment_parenthesis_close(t_lexer_args *args, t_token *token);
t_parse_status	err_unopened_parenthesis(t_lexer_args *args, t_token *token);
t_parse_status	err_unclosed_parenthesis(t_lexer_args *args, t_token *token);
t_parse_status	err_missing_left_operand(t_lexer_args *args, t_token *token);
t_parse_status	err_empty_parenthesis(t_lexer_args *args, t_token *token);
t_parse_status	err_empty_semicol(t_lexer_args *args, t_token *token);
t_parse_status	need_right_operand(t_lexer_args *args, t_token *token);
t_parse_status	get_error_message(t_token *token, char *msg);
t_parse_status	need_no_right_operand(t_lexer_args *args, t_token *token);
t_parse_status	err_missing_left_operand(t_lexer_args *args, t_token *token);
t_parse_status	err_no_left_operand(t_lexer_args *args, t_token *token);
t_parse_status	need_right_operand_no_parenthesis(t_lexer_args *args, t_token *token);

#endif