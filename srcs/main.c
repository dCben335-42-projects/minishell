/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:57:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/04 16:24:14 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messages.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "errors.h"

void execute_command(char **args) {
    if (fork() == 0) 
	{ 
		execvp(args[0], args);
		exit(1); 
	}
    wait(NULL);
}

char **create_args(char *input)
{
	char **args;

	args = ft_split(input, ' ');
	if (!args)
		error_malloc(NULL, NULL);
	return args;
}

int main(void) {
    char	*input;
    
    while (1)
	{
        input = readline(SHELL_NAME);
        if (!input) break;
        if (*input) add_history(input);

        execute_command(create_args(input));
        free(input);
    }
    return 0;
}
