/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:38:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/04 04:09:27 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct_shell.h"

# define ESC_START "\001"
# define ESC_END   "\002"

#define FIRST_COL     "\033[1;35m"
#define SECOND_COL    "\033[1;34m"
#define VARIANT_COL   "\033[1;36m"
#define ACCENT_COL    "\033[1;32m"
#define COMMAND_COL   "\033[33m"
#define RESET_COL     "\033[0m"

#define FIRST_COL_RL     "\001\033[1;35m\002"
#define SECOND_COL_RL    "\001\033[1;34m\002"
#define VARIANT_COL_RL   "\001\033[1;36m\002"
#define ACCENT_COL_RL    "\001\033[1;32m\002"
#define COMMAND_COL_RL   "\001\033[33m\002"
#define RESET_COL_RL     "\001\033[0m\002"







# define KEY_COL FIRST_COL
# define VALUE_COL SECOND_COL
# define BRACE_COL VARIANT_COL

void	close_fds(unsigned int start);
void	restore_std_in_out(int saved_stdin, int saved_stdout);

void	*destroy_self(t_shell *shell, char **argv, int exit_code);

char	*word_join(t_dynarray *word);

t_dynarray	*cmd_to_argv(t_shell *shell, t_dynarray *arr, t_dynarray *argv);

t_bool	p_int(int data, int error_value, const char *msg);
t_bool	s_int(int data, int error_value, const char *msg);
void	*p_ptr(void *data, const char *msg);
void	*s_ptr(void *data, const char *msg);

void	debug_exitcode(t_shell *shell);
void	debug_ast(t_shell *shell);
void	debug_tokens(t_shell *shell, t_dynarray *tokens);

void	*destroy_string(char *str);

const char *get_main_readline_arg(t_shell *shell);

#endif