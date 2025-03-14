/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:36:46 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/14 00:32:55 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft.h"

void	*p_ptr(void *data, const char *msg)
{
    if (!data)
	{
        perror(msg);
        return (NULL);
    }
    return (data);
}

t_bool	p_int(int data, int error_value, const char *msg)
{
	if (data == error_value)
	{
		perror(msg);
		return (FALSE);
	}
	return (TRUE);
}

void	*s_ptr(void *data, const char *msg)
{
	if (!data)
	{
		ft_putendl_fd((char *)msg, 2);
		return (NULL);
	}
	return (data);
}
