/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:38:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/06 03:02:05 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct_shell.h"

void		close_fds(unsigned int start);
void		restore_std_in_out(int saved_stdin, int saved_stdout);

void		*destroy_self(t_shell *shell, char **argv, int exit_code);

t_dynarray	*cmd_to_argv(t_shell *shell, t_dynarray *arr, t_dynarray *argv);

t_bool		p_int(int data, int error_value, const char *msg);
t_bool		s_int(int data, int error_value, const char *msg);
void		*p_ptr(void *data, const char *msg);
void		*s_ptr(void *data, const char *msg);

void		debug_exitcode(t_shell *shell);
void		debug_ast(t_shell *shell);
void		debug_tokens(t_shell *shell, t_dynarray *tokens);

const char	*get_main_readline_arg(t_shell *shell);

#endif