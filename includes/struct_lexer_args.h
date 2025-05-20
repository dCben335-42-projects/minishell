/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lexer_args.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:35:32 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/16 19:14:23 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_LEXER_ARGS_H
# define STRUCT_LEXER_ARGS_H

# include "struct_dynarray.h"
# include "struct_token.h"
# include "libft.h"

typedef struct s_bracket
{
	size_t		open;
	size_t		close;
}	t_bracket;

typedef enum e_right_operand_status
{
	DISALLOWED,
	UNDEFINED,
	REQUIRED,
	REQUIRED_WITHOUT_PAREN,
}	t_right_operand_status;

typedef struct s_lexer_args
{
	const char			*input;
	char				*error;
	char				quote;
	const char			*start;
	long				input_size;
	t_dynarray			tokens;
	t_bracket			parenthesis;
	t_bracket			bracket;
	t_right_operand_status	right_operand;
	
}	t_lexer_args;

t_lexer_args	init_lexer_args(const char *input);
void			*destroy_lexer_args(t_lexer_args *args);

#endif