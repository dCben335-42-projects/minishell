/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:38:38 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/22 16:48:13 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	close_fds(unsigned int start);
void	restore_std_in_out(int saved_stdin, int saved_stdout);

void	*destroy_self(t_shell *shell, char **argv, int exit_code);
char	*word_join(t_dynarray *word);

t_dynarray	*cmd_to_argv(t_shell *shell, t_dynarray *arr, t_dynarray *argv);

#endif