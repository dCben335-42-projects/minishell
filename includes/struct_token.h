/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:44:15 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:49:36 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_TOKEN_H
# define STRUCT_TOKEN_H

# include "types.h"

typedef enum e_token_type
{
	TOKEN_TEXT,
	TOKEN_VAR_TEXT,
	TOKEN_LITERAL_TEXT,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SEMICOL,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_BACKGROUND,
	TOKEN_PIPE_ERR,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_OPEN_BRACKET,
	TOKEN_CLOSE_BRACKET,
	TOKEN_UNKNOWN,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token_map
{
	char			*op;
	t_token_type	token;
}	t_token_map;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

t_token			*init_token(int token_type, const char *value,
					unsigned int start, size_t len);
void			*destroy_token(t_token *token);

const char		*get_token_type_name(const t_token_type type);
t_token_type	get_token_type(const char *str, int *offset);

t_bool			is_operator_token(t_token token);

#endif