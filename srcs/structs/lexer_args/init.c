/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:18 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/09 17:41:52 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_lexer_args.h"

/**
 * 
 * @brief Initializes the lexer arguments structure with the given input
 * 
 * @param input The input string to be processed by the lexer.
 * @param heredoc_cval A dynamic array to store heredoc values.
 * @param check_rules A boolean indicating whether to check rules
 * during lexing.
 * 
 * @return A t_lexer_args structure initialized with the given input
 * and heredoc values.
 * 
*/
t_lexer_args	init_lexer_args(
	const char *input,
	t_dynarray *heredoc_cval,
	t_bool check_rules
)
{
	t_lexer_args	args;

	args.base_input = (char *)input;
	args.input = input;
	args.quote = 0;
	args.parenthesis = (t_bracket){0, 0};
	args.is_heredoc = NOT_HEREDOC;
	args.tokens = init_dynarray(10, (void *(*)(void *))destroy_token);
	args.rhs = UNDEFINED;
	args.expected_rhs = UNDEFINED;
	args.not_finished_value = NULL;
	args.interrupted = FALSE;
	args.heredoc_cval = heredoc_cval;
	args.heredoc_ckey = 0;
	args.check_rules = check_rules;
	return (args);
}
