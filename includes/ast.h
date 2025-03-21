#ifndef AST_H
# define AST_H

# include "dynamic_array.h"

typedef enum {
    NODE_CMD,
    NODE_AND,
    NODE_OR,
    NODE_PIPE,
    NODE_SEQ
} node_type;

typedef struct ast_node {
    node_type type;
    t_dynamic_array	*command;
    struct ast_node *left;
    struct ast_node *right;
} ast_node;

void	ast_builder(t_dynamic_array *tokens);

#endif