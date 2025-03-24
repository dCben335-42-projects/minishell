#ifndef AST_H
# define AST_H

# include "dynamic_array.h"

//typedef enum {
//    NODE_CMD,
//    NODE_AND,
//    NODE_OR,
//    NODE_PIPE,
//    NODE_SEQ
//} node_type;

//typedef struct ast_node {
//    node_type type;
//    t_dynamic_array	*command;
//    struct ast_node *left;
//    struct ast_node *right;
//} ast_node;


typedef enum e_node_type 
{
    CMD_SEQ,
    CMD,
    CMD_TEXT,
    CMD_VAR_TEXT,
    CMD_LITERAL_TEXT,
    CMD_AND,
    CMD_OR,
    CMD_PIPE,
    CMD_PARENTHESIS_OPEN,
    CMD_PARENTHESIS_CLOSE
} t_node_type;

// Structure du nœud AST
typedef struct s_ast_node
{
    t_node_type type;
    //char *value;
    //struct s_ast_node **children;
    void    *content;
    int     child_count;
}   t_ast_node;

//void	ast_builder(t_dynamic_array *tokens);
t_ast_node  *create_node(t_node_type type, char *value);

#endif