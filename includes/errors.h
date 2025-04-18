/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:25:55 by bcabocel          #+#    #+#             */
/*   Updated: 2025/04/18 18:25:35 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "libft.h"
# include <stdio.h>

t_bool	p_int(int data, int error_value, const char *msg);
void	*p_ptr(void *data, const char *msg);
void	*s_ptr(void *data, const char *msg);

#endif