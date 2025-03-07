/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:28:37 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/07 17:23:37 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_pwd(t_shell *shell, char **args)
{
	char	*cwd;

    cwd = getcwd(NULL, 0); 
    if (!cwd)
    {
        perror("pwd"); 
        return;
    }
    printf("%s\n", cwd);
    free(cwd);
	(void)shell;
	(void)args;
}
