#ifndef CMD_H
# define CMD_H

int		command_handler(char *input, t_shell *shell);
t_bool	execute_cmd(char *path, char **args);

#endif