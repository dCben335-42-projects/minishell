#include "ast.h"
#include "dynamic_array.h"
#include "token.h"
#include <stdlib.h>
#include "parser_lexer.h"

t_ast_node	*create_node(t_node_type type, char *value)
{
    t_ast_node *node = malloc(sizeof(t_ast_node));
    if (!node) 
		return (NULL);
    node->type = type;
	if (value)
	{
		node->content = ft_strdup(value);
		node->child_count = 1;
		return (node);
	}
	node->content = NULL;
    node->child_count = 0;
    return (node);
}

void add_child(t_ast_node *parent, t_ast_node *child)
{
	t_dynamic_array	*sub_cmd;

	if (parent->child_count == 0)
	{
		sub_cmd = init_dynamic_array_malloc(6, NULL);
		set_value(sub_cmd, 0, child);
		parent->content = sub_cmd;
		parent->child_count = 2;
		return ;
	}
	set_value(parent->content, parent->child_count - 1, child);
	parent->child_count++;
}


void print_indentation(int depth)
{
	int depth_counter;

	depth_counter = 0;
	while (depth_counter < depth)
	{
		printf("  ");
		depth_counter++;
	}
}

void print_ast_json(t_dynamic_array	*cmd, int depth) {
	int i;
	t_ast_node *node;

    if (!cmd)
		return;
	i = 0;
	while (i < cmd->count)
	{
		//printf("i: %d\n", i);
		//printf("cmd->count: %d\n", cmd->count);
		//printf()
		node = (t_ast_node *)get_value(cmd, i);
		//printf("i: %d\n", i);
		//printf(node->type == CMD_SEQ ? "CMD_SEQ" :
		//	node->type == CMD ? "CMD" :
		//	node->type == CMD_AND ? "AND_CMD" :
		//	node->type == CMD_OR ? "OR_CMD" :
		//	node->type == CMD_PIPE ? "CMD_PIPE" :
		//	node->type == CMD_TEXT ? "CMD_TEXT" :
		//	node->type == CMD_VAR_TEXT ? "CMD_VAR_TEXT" :
		//	node->type == CMD_LITERAL_TEXT ? "CMD_LITERAL_TEXT" : "UNKNOWN");

		//printf("node->content: %s\n", (char *)node->content);
		
		if (node->type == CMD_SEQ)
		{
			print_indentation(depth);
			printf("{ type: 'CMD_SEQ', content: ");
			if (!node->content)
				printf("'null' }\n");
			if (node->child_count == 1)
				printf("'%s' }\n", (char *)node->content);
			if (node->child_count > 1)
			{
				printf("[\n");
				print_ast_json((t_dynamic_array *)node->content, depth + 2);
				print_indentation(depth);
				printf("]}\n");
			}
		}
		else if (node->type == CMD)
		{
			print_indentation(depth);
			printf("{ type: 'CMD', content: ");
			if (!node->content)
				printf("'null' }\n");
			if (node->child_count == 1)
				printf("'%s' }\n", (char *)node->content);
			if (node->child_count > 1)
			{
				printf("[\n");
				print_ast_json((t_dynamic_array *)node->content, depth + 2);
				print_indentation(depth);
				printf("]}\n");
			}
		}
		else if (node->type == CMD_AND)
		{
			print_indentation(depth);
			printf("{ type: 'CMD_AND', content: ");
			if (!node->content)
				printf("'null' }\n");
			if (node->child_count == 1)
				printf("'%s' }\n", (char *)node->content);
			if (node->child_count > 1)
			{
				printf("[\n");
				print_ast_json((t_dynamic_array *)node->content, depth + 2);
				print_indentation(depth);
				printf("]}\n");
			}
		}
		else if (node->type == CMD_OR)
		{
			print_indentation(depth);
			printf("{ type: 'CMD_OR', content: ");
			if (!node->content)
				printf("'null' }\n");
			if (node->child_count == 1)
				printf("'%s' }\n", (char *)node->content);
			if (node->child_count > 1)
			{
				printf("[\n");
				print_ast_json((t_dynamic_array *)node->content, depth + 2);
				print_indentation(depth);
				printf("]}\n");
			}
		}
		else if (node->type == CMD_PIPE)
		{
			print_indentation(depth);
			printf("{ type: 'CMD_PIPE', content: ");
			if (!node->content)
				printf("'null' }\n");
			if (node->child_count == 1)
				printf("'%s' }\n", (char *)node->content);
			if (node->child_count > 1)
			{
				printf("[\n");
				print_ast_json((t_dynamic_array *)node->content, depth + 2);
				print_indentation(depth);
				printf("]}\n");
			}
		}
		else if (node->type == CMD_TEXT)
		{
			print_indentation(depth);
			printf("{ type: 'CMD_TEXT', content: ");
			if (!node->content)
				printf("'null' }\n");
			if (node->child_count == 1)
				printf("'%s' }\n", (char *)node->content);
			if (node->child_count > 1)
			{
				printf("[\n");
				print_ast_json((t_dynamic_array *)node->content, depth + 2);
				print_indentation(depth);
				printf("]}\n");
			}
		}
		else if (node->type == CMD_LITERAL_TEXT)
		{
			print_indentation(depth);
			printf("{ type: 'CMD_LITERAL_TEXT', content: ");
			if (!node->content)
				printf("'null' }\n");
			if (node->child_count == 1)
				printf("'%s' }\n", (char *)node->content);
			if (node->child_count > 1)
			{
				printf("[\n");
				print_ast_json((t_dynamic_array *)node->content, depth + 2);
				print_indentation(depth);
				printf("]}\n");
			}
		}
		else if (node->type == CMD_VAR_TEXT)
		{
			print_indentation(depth);
			printf("{ type: 'CMD_VAR_TEXT', content: ");
			if (!node->content)
				printf("'null' }\n");
			if (node->child_count == 1)
				printf("'%s' }\n", (char *)node->content);
			if (node->child_count > 1)
			{
				printf("[\n");
				print_ast_json((t_dynamic_array *)node->content, depth + 2);
				print_indentation(depth);
				printf("]}\n");
			}
		}
		i++;
	}




    //for (int i = 0; i < depth; i++) printf("  ");






	//t_ast_node *node = (t_ast_node *)get_value(cmd, 0);



	//t_ast(* t_ast_node)get_value(cmd, 0);

    //printf("{ \"type\": \"%s\"",
    //       node->type == CMD_SEQ ? "CMD_SEQ" :
    //       node->type == CMD ? "CMD" :
    //       node->type == CMD_AND ? "AND_CMD" :
    //       node->type == CMD_OR ? "OR_CMD" :
    //       node->type == CMD_PIPE ? "CMD_PIPE" : "UNKNOWN");

    //if (node->value) {
    //    printf(", \"value\": \"%s\"", node->value);
    //}

    //if (node->child_count > 0) {
    //    printf(", \"children\": [\n");
    //    for (int i = 0; i < node->child_count; i++) {
    //        print_ast_json(node->children[i], depth + 2);
    //        if (i < node->child_count - 1) printf(",");
    //        printf("\n");
    //    }
    //    for (int i = 0; i < depth; i++) printf("  ");
    //    printf("]");
    //}

    //printf("}");
}

// Libération mémoire
//void free_ast(t_ast_node *node) {
//    if (!node) return;
//    free(node->value);
//    for (int i = 0; i < node->child_count; i++) {
//        free_ast(node->children[i]);
//    }
//    free(node->children);
//    free(node);
//}

void print_ast_json_wrapper(t_dynamic_array *cmd)
{
	printf("[\n");
	print_ast_json(cmd, 2);
	printf("]\n");
}


t_ast_node *convert_token_to_cmd(t_token *token)
{
	if (token->type == TOKEN_TEXT)
		return (create_node(CMD_TEXT, token->value));
	else if (token->type == TOKEN_VAR_TEXT)
		return (create_node(CMD_VAR_TEXT, token->value));
	else if (token->type == TOKEN_LITERAL_TEXT)
		return (create_node(CMD_LITERAL_TEXT, token->value));
	else if (token->type == TOKEN_PIPE)
		return (create_node(CMD_PIPE, NULL));
	else if (token->type == TOKEN_AND)
		return (create_node(CMD_AND, NULL));
	else if (token->type == TOKEN_OR)
		return (create_node(CMD_OR, NULL));
	return (NULL);
}


t_ast_node *get_cmd(t_dynamic_array *tokens, int *i)
{
	t_ast_node *new_cmd;
	t_token *token;

	new_cmd = NULL;
	if (*i >= tokens->count)
		return (NULL);
	token = (t_token *)get_value(tokens, *i);
	if (!is_operator_token(*token))
	{
		//printf("i=%d\n",*i);
		while (*i < tokens->count && !is_operator_token(*token))
		{
			//printf("token->value: %s\n", token->value);
			if (!new_cmd)
				new_cmd = create_node(CMD, NULL);
			add_child(new_cmd, convert_token_to_cmd(token));
			(*i)++;
			if (*i < tokens->count)
				token = (t_token *)get_value(tokens, *i);
		}
	}
	else
	{
		//printf("ERROR\n");
		(*i)++;
		return (convert_token_to_cmd(token));
	}	
	return (new_cmd);
}






int main() {
	int i;
	int pos;
	t_ast_node *new_cmd;
	t_ast_node *new_cmd2;
	t_ast_node *new_cmd3;
	t_ast_node *new_cmd4;
	t_dynamic_array	*cmd = init_dynamic_array_malloc(20, NULL);
	t_dynamic_array *tokens = init_dynamic_array_malloc(20, NULL);
	set_value(tokens, 0, init_token(TOKEN_TEXT, "ls", 0, 2));
	set_value(tokens, 1, init_token(TOKEN_TEXT, "-l", 0, 2));
	set_value(tokens, 2, init_token(TOKEN_AND, "&&", 0, 2));
	set_value(tokens, 3, init_token(TOKEN_TEXT, "echo", 0, 4));
	set_value(tokens, 4, init_token(TOKEN_VAR_TEXT, "hello", 0, 5));
	set_value(tokens, 5, init_token(TOKEN_AND, "&&", 0, 2));
	set_value(tokens, 6, init_token(TOKEN_TEXT, "cat", 0, 3));
	set_value(tokens, 7, init_token(TOKEN_LITERAL_TEXT, "file.txt", 0, 8));
	set_value(tokens, 8, init_token(TOKEN_PIPE, "|", 0, 1));
	set_value(tokens, 9, init_token(TOKEN_LITERAL_TEXT, "output.txt", 0, 10));
	set_value(tokens, 10, init_token(TOKEN_AND, "&&", 0, 2));
	set_value(tokens, 11, init_token(TOKEN_TEXT, "echo", 0, 4));
	set_value(tokens, 12, init_token(TOKEN_LITERAL_TEXT, "jojo", 0, 4));
	set_value(tokens, 13, init_token(TOKEN_OR, "||", 0, 2));
	set_value(tokens, 14, init_token(TOKEN_TEXT, "echo", 0, 4));
	set_value(tokens, 15, init_token(TOKEN_LITERAL_TEXT, "tata", 0, 4));
	// ls -l && echo "hello" && cat file.txt | output.txt && echo "jojo" || echo "tata"

	i = 0;
	pos = 0;
	new_cmd = get_cmd(tokens, &i);
	set_value(cmd, pos, new_cmd);
	pos++;
	while (i < tokens->count)
	{
		new_cmd = get_cmd(tokens, &i);
		if (new_cmd->type != CMD)
		{
			new_cmd2 = get_cmd(tokens, &i);
			new_cmd3 = get_cmd(tokens, &i);
			if (new_cmd3 && new_cmd3->type == CMD_PIPE)
			{
				add_child(new_cmd3, new_cmd2);
				new_cmd4 = get_cmd(tokens, &i);
				add_child(new_cmd3, new_cmd4);
				add_child(new_cmd, new_cmd3);
			}
			else
			{
				if (new_cmd3)
					i--;
				add_child(new_cmd, new_cmd2);
			}
		}
		set_value(cmd, pos, new_cmd);
		pos++;
	}
	print_ast_json_wrapper(cmd);
    return 0;
}

//cc srcs/ast_builder/ast_builder.c libs/libft/srcs/**/*.c srcs/structs/**/*.c -I includes -I libs/libft/includes












//ast_node	*create_node(node_type type, t_dynamic_array *command, ast_node *left, ast_node *right)
//{
//    ast_node *node = malloc(sizeof(ast_node));
//    if (!node)
//		return (NULL);
//    node->type = type;
//	node->command = command;
//    node->left = left;
//    node->right = right;
//    return (node);
//}







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

//t_dynamic_array	*get_cmd_part(t_dynamic_array *tokens, t_uint *i)
//{
//	t_dynamic_array *new_dyn_array = init_dynamic_array_malloc(10, NULL);
//	t_token	*token;
//	t_uint count;

//	count = 0;
//	while (*i < tokens->count)
//	{
//		token = (tokens->data)[*i];
//		if (token->type == TOKEN_TEXT || token->type == TOKEN_VAR_TEXT || token->type == TOKEN_LITERAL_TEXT)
//			set_value(new_dyn_array, count++, init_token(token->type, token->value, 0, ft_strlen(token->value)));
//		else
//			break;
//		(*i)++;
//	}
//	return (new_dyn_array);
//}















//void ast_builder(t_dynamic_array *tokens)
//{
//	t_dynamic_array *cmd_part;
//	t_uint i;
//	t_token *token;
//	ast_node *node_left;
//	ast_node *node_right;
//	ast_node *node_middle;

//	i = 0;
//	cmd_part = get_cmd_part(tokens, &i);
//	node_left = create_node(NODE_CMD, cmd_part, NULL, NULL);
//	printf("------------------AST-------------------\n");
//	print_tokens(cmd_part);
	

//	destroy_dynamic_array(cmd_part);
//	free(cmd_part);

//	if (i < tokens->count)
//	{
//		token = (tokens->data)[i];
//		if (token->type != TOKEN_EOF)
//		{
//			i++;
//			cmd_part = get_cmd_part(tokens, &i);
//			node_right = create_node(NODE_CMD, cmd_part, NULL, NULL);
//			printf("------------------AST-------------------\n");
//			print_tokens(cmd_part);
//			destroy_dynamic_array(cmd_part);
//			free(cmd_part);
//		}
//	}



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
//}