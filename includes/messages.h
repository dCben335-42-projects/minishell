/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcabocel <bcabocel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:39:44 by bcabocel          #+#    #+#             */
/*   Updated: 2025/05/23 22:31:24 by bcabocel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# include <stdio.h>

# define SHELL_NAME "Minishell"

# define ERROR_MALLOC "Error: malloc"

# define ERR_CD "cd"
# define ERR_CD_HOME "cd: HOME not set"
# define ERR_CD_OLDPWD "cd: OLDPWD not set"
# define ERR_CD_ARGS "cd: too many arguments"

# define ERR_GETCWD \
"chdir: error retrieving current directory: \
getcwd: cannot access parent directories"

# define ERR_PWD \
"minishell: pwd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory"

# define ERROR_SHELL_INIT \
"shell-init: error retrieving current directory: \
getcwd: cannot access parent directories"

# define EXIT_MSG "exit"
# define ERROR_EXIT_ARGS_NUM "exit: too many arguments"
# define ERROR_EXIT_NUM "exit: numeric argument required"

# define EXPORT_PREFIX "export "
# define ERR_EXPORT_ID "export: '%s': not a valid identifier\n"

# define ERR_NOT_FOUND "minishell: command not found: "

# define SYNTAX_ERR_START "syntax error near unexpected token `"
# define SYNTAX_ERR_END "'\n"

#endif