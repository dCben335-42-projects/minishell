/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lexer_args.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:35:32 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/29 16:04:32 by abonneau         ###   ########.fr       */
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

typedef enum e_rhs_status
{
	DISALLOWED,
	UNDEFINED,
	REQUIRED,
	REQUIRED_WITHOUT_PAREN,
}	t_rhs_status;

typedef enum e_is_heredoc
{
	NOT_HEREDOC,
	HEREDOC,
	HEREDOC_TRIM,
}	t_is_heredoc;

#define HEREDOC_EXPANDABLE_TRUE		"expandable=true"
#define HEREDOC_EXPANDABLE_FALSE	"expandable=false"

typedef struct s_lexer_args
{
	char 				*base_input;
	const char			*input;
	char				quote;
	t_is_heredoc		is_heredoc;
	t_dynarray			tokens;
	t_bracket			parenthesis;
	t_rhs_status		rhs;
	t_rhs_status		expected_rhs;
	const char			*not_finished_value;
	t_bool				heredoc_interupted;
	t_dynarray			*heredoc_cval;
	t_uint				heredoc_ckey;
}	t_lexer_args;

typedef struct s_readline_state
{
	t_token_type	type;
	const char		*value;
}	t_readline_state;

t_lexer_args	init_lexer_args(const char *input, t_dynarray *heredoc_cval);
void			*destroy_lexer_args(t_lexer_args *args, t_bool destroy_heredocs);

const char *get_readline_arg(t_token_type type);

# define READLINE_S_QUOTE_KEY		-1
# define READLINE_D_QUOTE_KEY		-2
# define READLINE_S_QUOTE_VAL 		"single_quote>"
# define READLINE_D_QUOTE_VAL 		"double_quote>"
# define READLINE_PARENTHESIS_VAL 	"subshell>"
# define READLINE_HEREDOC_VAL 		"heredoc>"
# define READLINE_HEREDOC_TRIM_VAL 	"dash_heredoc>"
# define READLINE_AND_VAL			"and>"
# define READLINE_OR_VAL			"or>"
# define READLINE_PIPE_VAL			"pipe>"
# define READLINE_HEREDOC_VAL		"heredoc>"
# define READLINE_HEREDOC_TRIM_VAL	"dash_heredoc>"

#endif