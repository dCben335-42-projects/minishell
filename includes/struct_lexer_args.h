/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lexer_args.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:35:32 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/28 20:50:44 by abonneau         ###   ########.fr       */
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
}	t_lexer_args;

t_lexer_args	init_lexer_args(const char *input);
void			*destroy_lexer_args(t_lexer_args *args);

#endif