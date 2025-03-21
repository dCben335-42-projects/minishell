#include "ast.h"
#include "dynamic_array.h"
#include "token.h"
#include <stdlib.h>
#include "parser_lexer.h"

ast_node	*create_node(node_type type, t_dynamic_array *command, ast_node *left, ast_node *right)
{
    ast_node *node = malloc(sizeof(ast_node));
    if (!node)
		return (NULL);
    node->type = type;
	node->command = command;
    node->left = left;
    node->right = right;
    return (node);
}

//get_cmd_part(t_dynamic_array *tokens, int *i)
//{
//	t_token	*token;
//	t_token	**command;
//	size_t 	count;
//	int start = *i;

//	while (*i < tokens->count)
//	{
//		token = (tokens->data)[*i];
//		if (token->type == TOKEN_TEXT || token->type == TOKEN_VAR_TEXT || token->type == TOKEN_LITERAL_TEXT)
//			count++;
//		else
//			break;
//		(*i)++;
//	}
//	command = malloc(sizeof(t_token *) * count);
//	if (!command)
//		return (NULL);
//	*i = start;
//	while (*i)
//	{
//		token = (tokens->data)[*i];
//		if (token->type == TOKEN_TEXT || token->type == TOKEN_VAR_TEXT || token->type == TOKEN_LITERAL_TEXT)
//			command[*i] = token;
//		else
//			break;
//		(*i)++;
//	}
//}

t_dynamic_array	*get_cmd_part(t_dynamic_array *tokens, t_uint *i)
{
	t_dynamic_array *new_dyn_array = init_dynamic_array_malloc(10, NULL);
	t_token	*token;
	t_uint count;

	count = 0;
	while (*i < tokens->count)
	{
		token = (tokens->data)[*i];
		if (token->type == TOKEN_TEXT || token->type == TOKEN_VAR_TEXT || token->type == TOKEN_LITERAL_TEXT)
			set_value(new_dyn_array, count++, init_token(token->type, token->value, 0, ft_strlen(token->value)));
		else
			break;
		(*i)++;
	}
	return (new_dyn_array);
}















void ast_builder(t_dynamic_array *tokens)
{
	t_dynamic_array *cmd_part;
	t_uint i;
	t_token *token;
	ast_node *node_left;
	ast_node *node_right;
	ast_node *node_middle;

	i = 0;
	cmd_part = get_cmd_part(tokens, &i);
	node_left = create_node(NODE_CMD, cmd_part, NULL, NULL);
	printf("------------------AST-------------------\n");
	print_tokens(cmd_part);
	

	destroy_dynamic_array(cmd_part);
	free(cmd_part);

	if (i < tokens->count)
	{
		token = (tokens->data)[i];
		if (token->type != TOKEN_EOF)
		{
			i++;
			cmd_part = get_cmd_part(tokens, &i);
			node_right = create_node(NODE_CMD, cmd_part, NULL, NULL);
			printf("------------------AST-------------------\n");
			print_tokens(cmd_part);
			destroy_dynamic_array(cmd_part);
			free(cmd_part);
		}
	}



	//int	i;
	//t_token	*token;
	//t_token	**cmd_part;
	//t

	//i = 0;

	//while (i < tokens->count)
	//{
	//	token = (tokens->data)[i];
	//	if (token->type == TOKEN_TEXT || token->type == TOKEN_VAR_TEXT || token->type == TOKEN_LITERAL_TEXT)
	//	{
	//		i++;
	//		//t_token *cmd_part = init_token(token->type, token->value, 0, ft_strlen(token->value));
	//		//cmd_part = (char *)malloc(ft_strlen(token->value) * sizeof(char));
	//		// create_node(NODE_CMD, token->value, NULL, NULL);
	//	}

	//	//ft_strlen(tokens->data[i].value);
	//	//malloc(tokens->data[i].value);
	//	i++;
	//}
}