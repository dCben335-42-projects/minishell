/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:36:46 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/13 15:30:36 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"
#include "errors.h"

void	*perror_wrapper(void *data, char *msg)
{
	if (!data)
	{
		perror(msg);
		return (NULL);
	}
	return (data);
}
