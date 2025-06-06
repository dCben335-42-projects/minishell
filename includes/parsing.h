/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:45:18 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/06 03:04:42 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include "libft.h"
# include "config.h"
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

t_ptr			get_token(t_lexer_args *args);
t_ptr			get_next_token(t_lexer_args *args);
t_bool			get_prev_token(t_lexer_args *args, t_token **prev_token);

t_ptr			transform_heredoc(t_lexer_args *args);
int				read_heredoc_if_possible(t_lexer_args *args, t_token *token);
t_parse_status	read_heredoc(
					t_lexer_args *args,
					t_token *token,
					const t_bool is_expandable);

t_ptr			tokenize_whitespace(t_lexer_args *args);
t_ptr			tokenize_word(t_lexer_args *args);
t_ptr			tokenize_wildcard(
					t_lexer_args *args,
					t_token_type *current_type);
t_ptr			tokenize_expand(
					t_lexer_args *args,
					char **start_i,
					t_token_type *current_type);
t_ptr			tokenize_enclosures(
					t_lexer_args *args,
					char **start_i,
					t_token_type *current_type);
t_ptr			tokenize_operator(
					t_lexer_args *args,
					int offset,
					t_token_type type);

t_token_type	quoted_wrapper(t_lexer_args *args, t_token_type *current_type);
t_bool			need_tokenize(t_lexer_args *args, char **start_i);
t_ptr			wrap_ptr_token(
					t_lexer_args *args,
					t_token_type *current_type,
					char **start_i,
					size_t optional_len);

typedef struct s_rules_map
{
	t_token_flag	key;
	t_parse_status	(*f)(t_lexer_args	*args, t_token	*token);
}	t_rules_map;

t_parse_status	token_parser(t_lexer_args *args, t_token *token);
t_parse_status	check_all_rules(t_lexer_args *args, t_token *token);

t_parse_status	inc_parenthesis_open(t_lexer_args *args, t_token *token);
t_parse_status	inc_parenthesis_close(t_lexer_args *args, t_token *token);

t_parse_status	err_unopened_parenthesis(t_lexer_args *args, t_token *token);
t_parse_status	err_unclosed_parenthesis(t_lexer_args *args, t_token *token);
t_parse_status	err_miss_left_operand(t_lexer_args *args, t_token *token);
t_parse_status	err_unexp_left_operand(t_lexer_args *args, t_token *token);
t_parse_status	err_unexp_right_operand(t_lexer_args *args, t_token *token);
t_parse_status	err_empty_parenthesis(t_lexer_args *args, t_token *token);
t_parse_status	err_empty_semicol(t_lexer_args *args, t_token *token);
t_parse_status	err_miss_right_operand(t_lexer_args *args, t_token *token);
t_parse_status	err_miss_right_operand_np(t_lexer_args *args, t_token *token);

t_parse_status	print_error_message(t_token *token, char *msg);

#endif