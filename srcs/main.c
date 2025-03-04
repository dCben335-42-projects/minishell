/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:57:59 by bcabocel          #+#    #+#             */
/*   Updated: 2025/03/04 16:06:17 by bcabocel         ###   ########.fr       */
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

void execute_command(char **args) {
    if (fork() == 0) 
	{ 
		execvp(args[0], args);
		exit(1); 
	}
    wait(NULL);
}

int main(void) {
    char *input;
    char **args;
    
    while (1)
	{
        input = readline(SHELL_NAME);
        if (!input) break;
        if (*input) add_history(input);

        args = malloc(64 * sizeof(char *));
        char *token = strtok(input, " ");
        int i = 0;
        while (token)
		{
			args[i++] = token;
			token = strtok(NULL, " "); 
		}
        args[i] = NULL;

        execute_command(args);
        free(input);
    }
    return 0;
}
