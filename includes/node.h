#ifndef NODE_H
# define NODE_H

# include "dynamic_array.h"
# include "token.h"
# include "libft.h"
# include <stdio.h>

typedef enum e_node_type 
{
    CMD_SEQ,
    CMD_PARENTHESIS,
    CMD,
    CMD_TEXT,
    CMD_VAR_TEXT,
    CMD_LITERAL_TEXT,
    CMD_AND,
    CMD_OR,
    CMD_PIPE,
    CMD_PARENTHESIS_OPEN,
    CMD_PARENTHESIS_CLOSE,
    CMD_APPEND,
    CMD_REDIR_IN,
    CMD_REDIR_OUT,
    CMD_HEREDOC,
    CMD_SPACE,
    CMD_EOF
} t_node_type;

typedef struct s_ast_node
{
    t_node_type type;
    void    *content;
    int     child_count;
}   t_ast_node;

typedef struct s_ast_print_mapping
{
    int type;
    const char *name;
    int use_cmd_join;
}   t_ast_print_mapping;

typedef struct s_print_ast_json_args
{
    t_dynamic_array     *cmd;
    int                 depth;
    t_ast_print_mapping *mappings;
}   t_print_ast_json_args;

t_ast_node  *init_node(t_node_type type, char *value);
t_ast_node	*convert_token_to_cmd(t_token *token);
int         add_child(t_ast_node *parent, t_ast_node *child);
void		print_ast_json_wrapper(t_dynamic_array *cmd);
void		print_ast_json(t_print_ast_json_args args);
void		print_cmd_type(t_node_type type);

#endif