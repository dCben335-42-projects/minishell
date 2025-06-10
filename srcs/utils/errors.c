/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:36:46 by bcabocel          #+#    #+#             */
/*   Updated: 2025/06/10 02:52:36 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/**
 * @brief Function that use perror and print the message
 * if the pointer is NULL
 * 
 * @param data: pointer to check
 * @param msg: message to print in case of NULL ptr
 * 
 * @return data if not NULL, NULL otherwise
 */
void	*p_ptr(void *data, const char *msg)
{
	if (!data)
	{
		perror(msg);
		return (NULL);
	}
	return (data);
}

/**
 * @brief Function that use perror and print the message
 * if the pointer is equal to error_value
 * 
 * @param data: data to check
 * @param error_value: value to compare with
 * @param msg: message to print in case of error
 * 
 * @return TRUE if data is not equal to error_value, FALSE otherwise
 */
t_bool	p_int(int data, int error_value, const char *msg)
{
	if (data == error_value)
	{
		perror(msg);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Function that print the message in the error stream
 * if the pointer is NULL
 
 * @param ptr: pointer to check
 * @param msg: message to print in case of NULL ptr
 * 
 * @return data if not NULL, NULL otherwise
 */
void	*s_ptr(void *ptr, const char *msg)
{
	if (!ptr)
	{
		ft_putendl_fd(msg, 2);
		return (NULL);
	}
	return (ptr);
}

/**
 * @brief Function that print the message in the error stream
 * if the pointer is equal to error_value
 * 
 * @param data: data to check
 * @param error_value: value to compare with
 * @param msg: message to print in case of error
 * 
 * @return TRUE if data is not equal to error_value, FALSE otherwise
 */
t_bool	s_int(int data, int error_value, const char *msg)
{
	if (data == error_value)
	{
		ft_putendl_fd(msg, 2);
		return (FALSE);
	}
	return (TRUE);
}
