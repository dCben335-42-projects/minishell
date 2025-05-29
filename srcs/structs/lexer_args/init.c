/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:18:18 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/29 15:15:58 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_lexer_args.h"

t_lexer_args	init_lexer_args(const char *input, t_bool check_rules)
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
	args.check_rules = check_rules;
	return (args);
}
