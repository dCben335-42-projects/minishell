#include "ast.h"
#include "dynamic_array.h"
#include "token.h"
#include <stdlib.h>
#include "parser_lexer.h"

void print_ast_json(t_print_ast_json_args args);
int count_token_between_brackets(t_dynamic_array *tokens, int i);
int	get_and_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev);
t_dynamic_array	*get_cmd_master(t_get_cmd_master args);

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
		sub_cmd = init_dynamic_array_malloc(40, NULL);
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

void print_ast_node_json(t_ast_node *node, int i, char *node_type, t_print_ast_json_args args)
{
	print_indentation(args.depth);
	printf("{ type: '%s', content: ", node_type);
	if (!node->content)
		printf("'null' }\n");
	if (node->child_count == 1)
		printf("'%s' }\n", (char *)node->content);
	if (node->child_count > 1)
	{
		printf("[\n");
		print_ast_json((t_print_ast_json_args){(t_dynamic_array *)node->content, args.depth + 2});
		print_indentation(args.depth);
		printf("]}");
		if (i < args.cmd->count - 1)
			printf(",");
		printf("\n");
	}
}

void print_ast_json(t_print_ast_json_args args) {
	int i;
	t_ast_node *node;

    if (!args.cmd)
		return;
	i = 0;
	while (i < args.cmd->count)
	{
		node = (t_ast_node *)get_value(args.cmd, i);
		
		// duizhjduzhd
		if (node->type == CMD_SEQ)
		{
			print_ast_node_json(node, i, "CMD_SEQ", args);
		}
		else if (node->type == CMD)
		{
			print_ast_node_json(node, i, "CMD", args);
		}
		else if (node->type == CMD_AND)
		{
			print_ast_node_json(node, i, "CMD_AND", args);
		}
		else if (node->type == CMD_OR)
		{
			print_ast_node_json(node, i, "CMD_OR", args);
		}
		else if (node->type == CMD_PIPE)
		{
			print_ast_node_json(node, i, "CMD_PIPE", args);
		}
		else if (node->type == CMD_TEXT)
		{
			print_ast_node_json(node, i, "CMD_TEXT", args);
		}
		else if (node->type == CMD_LITERAL_TEXT)
		{
			print_ast_node_json(node, i, "CMD_LITERAL_TEXT", args);
		}
		else if (node->type == CMD_VAR_TEXT)
		{
			print_ast_node_json(node, i, "CMD_VAR_TEXT", args);
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
	print_ast_json((t_print_ast_json_args){cmd, 2});
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
	else if (token->type == TOKEN_OPEN_BRACKET)
		return (create_node(CMD_PARENTHESIS_OPEN, NULL));
	else if (token->type == TOKEN_CLOSE_BRACKET)
		return (create_node(CMD_PARENTHESIS_CLOSE, NULL));
	else if (token->type == TOKEN_EOF)
		return (create_node(CMD_EOF, NULL));
	return (NULL);
}

void print_cmd_type(t_node_type type)
{
	if (type == CMD_SEQ)
		printf("CMD_SEQ\n");
	else if (type == CMD)
		printf("CMD\n");
	else if (type == CMD_TEXT)
		printf("CMD_TEXT\n");
	else if (type == CMD_VAR_TEXT)
		printf("CMD_VAR_TEXT\n");
	else if (type == CMD_LITERAL_TEXT)
		printf("CMD_LITERAL_TEXT\n");
	else if (type == CMD_AND)
		printf("CMD_AND\n");
	else if (type == CMD_OR)
		printf("CMD_OR\n");
	else if (type == CMD_PIPE)
		printf("CMD_PIPE\n");
	else if (type == CMD_PARENTHESIS_OPEN)
		printf("CMD_PARENTHESIS_OPEN\n");
	else if (type == CMD_PARENTHESIS_CLOSE)
		printf("CMD_PARENTHESIS_CLOSE\n");
	else if (type == CMD_EOF)
		printf("CMD_EOF\n");
}

int get_seq_cmd(t_get_cmd_master args, t_dynamic_array *cmd_master, int *i, int *pos)
{
	t_dynamic_array *sub_cmd;
	int count;

	count = count_token_between_brackets(args.tokens, *i);
	//printf("count: %d\n", count);
	sub_cmd = get_cmd_master((t_get_cmd_master){args.tokens, *i, *i + count});
	//printf("%d =---------------------\n", count);
	//print_ast_json_wrapper(sub_cmd);
	set_value(cmd_master, *pos, sub_cmd);
	*i += count + 1;
	return (1);
}

int get_parenthesis_cmd(t_get_cmd_master args, t_ast_node *cmd_master, int *i)
{
	t_dynamic_array *sub_cmd;
	int sub_cmd_count;
	int count;

	sub_cmd_count = 0;
	count = count_token_between_brackets(args.tokens, *i);
	//printf("count: %d\n", count);
	sub_cmd = get_cmd_master((t_get_cmd_master){args.tokens, *i, *i + count});
	//printf("%d =---------------------\n", count);
	//print_ast_json_wrapper(sub_cmd);
	while (sub_cmd_count < sub_cmd->count)
	{
		add_child(cmd_master, (t_ast_node *)get_value(sub_cmd, sub_cmd_count));
		sub_cmd_count++;
	}
	*i += count + 1;
	return (1);
}

t_ast_node *get_cmd(t_dynamic_array *tokens, int *i, int end)
{
	t_ast_node *new_cmd;
	t_token *token;

	new_cmd = NULL;
	if (*i >= end)
		return (NULL);
	token = (t_token *)get_value(tokens, *i);
	if (is_text_token(*token))
	{
		while (*i < end && !is_operator_token(*token))
		{
			if (!new_cmd)
				new_cmd = create_node(CMD, NULL);
			add_child(new_cmd, convert_token_to_cmd(token));
			(*i)++;
			if (*i < end)
				token = (t_token *)get_value(tokens, *i);
		}
	}
	else
	{
		(*i)++;
		return (convert_token_to_cmd(token));
	}	
	return (new_cmd);
}


int	get_pipe_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev)
{
	t_ast_node *cmd;

	while (*i < args.end)
	{
		cmd = get_cmd(args.tokens, i, args.end);
		if (*i == args.end)
		{
			add_child(cmd_master, cmd);
			return (1);
		}
		else if (cmd->type == CMD_PIPE)
		{
			add_child(cmd_master, *cmd_prev);
		}
		else if (cmd->type != CMD)
		{
			(*i)--;
			add_child(cmd_master, *cmd_prev);
			*cmd_prev = NULL;
			return (1);
		}
		else if (cmd->type == CMD)
		{
			*cmd_prev = cmd;
		}
	}
	return (1);
}

int	get_and_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev)
{
	t_ast_node *cmd;
	t_dynamic_array *sub_cmd;
	int sub_cmd_count;

	sub_cmd_count = 0;
	while (*i < args.end)
	{
		cmd = get_cmd(args.tokens, i, args.end);
		//print_cmd_type(cmd->type);
		if (*i == args.end)
		{
			add_child(cmd_master, cmd);
			return (1);
		}
		if (cmd->type == CMD_PIPE)
		{
			add_child(cmd, *cmd_prev);
			if (get_pipe_cmd(cmd, args, i, cmd_prev) == 1)
			{
				add_child(cmd_master, cmd);
			}
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
			get_parenthesis_cmd(args, cmd_master, i);
		else if (cmd->type == CMD_AND)
		{
			(*i)--; // on revient en arrière pour traiter le AND
			if (*cmd_prev)
				add_child(cmd_master, *cmd_prev);
			return (1);
		}
		else if (cmd->type == CMD_OR)
		{
			(*i)--; // on revient en arrière pour traiter le OR
			if (*cmd_prev)
				add_child(cmd_master, *cmd_prev);
			return (1);
		}
		else
		{
			*cmd_prev = cmd;
		}
	}
	return (1);
}

int	get_or_cmd(t_ast_node *cmd_master, t_get_cmd_master args, int *i, t_ast_node **cmd_prev)
{
	t_ast_node *cmd;

	while (*i < args.end)
	{
		cmd = get_cmd(args.tokens, i, args.end);
		if (*i == args.end)
		{
			add_child(cmd_master, cmd);
			return (1);
		}
		if (cmd->type == CMD_PIPE)
		{
			add_child(cmd, *cmd_prev);
			if (get_pipe_cmd(cmd, args, i, cmd_prev) == 1)
			{
				add_child(cmd_master, cmd);
			}
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
			get_parenthesis_cmd(args, cmd_master, i);
		else if (cmd->type == CMD_AND)
		{
			(*i)--; // on revient en arrière pour traiter le AND
			if (*cmd_prev)
				add_child(cmd_master, *cmd_prev);
			return (1);
		}
		else if (cmd->type == CMD_OR)
		{
			(*i)--; // on revient en arrière pour traiter le OR
			if (*cmd_prev)
				add_child(cmd_master, *cmd_prev);
			return (1);
		}
		else
		{
			*cmd_prev = cmd;
		}
	}
	return (1);
}

int count_token_between_brackets(t_dynamic_array *tokens, int i)
{
	int count;
	int count_parenthesis_open;
	int count_parenthesis_close;
	t_token *token;

	count = 0;
	count_parenthesis_open = 1;
	count_parenthesis_close = 0;
	while (i < tokens->count - 1)
	{
		token = (t_token *)get_value(tokens, i);
		if (token->type == TOKEN_OPEN_BRACKET)
			count_parenthesis_open++;
		else if (token->type == TOKEN_CLOSE_BRACKET)
			count_parenthesis_close++;
		if (count_parenthesis_open == count_parenthesis_close)
			return (count);
		count++;
		i++;
	}
	return (count);
}

t_dynamic_array	*get_cmd_master(t_get_cmd_master args)
{
	int i;
	int pos;
	t_ast_node *cmd_prev;
	t_ast_node *cmd;
	t_dynamic_array	*cmd_master = init_dynamic_array_malloc(40, NULL);
	(void)args.end;

	i = args.start;
	pos = 0;
	cmd_prev = NULL;
	while (i < args.end)
	{
		cmd = get_cmd(args.tokens, &i, args.end);
		if (i == args.end)
		{
			set_value(cmd_master, pos, cmd);
		}
		if (cmd->type == CMD_PIPE)
		{
			add_child(cmd, cmd_prev);
			if (get_pipe_cmd(cmd, args, &i, &cmd_prev) == 1)
			{
				set_value(cmd_master, pos, cmd);
				pos++;
			}
		}
		else if (cmd->type == CMD_AND)
		{
			if (pos == 0)
			{
				set_value(cmd_master, pos, cmd_prev);
				pos++;
			}
			if (get_and_cmd(cmd, args, &i, &cmd_prev))
			{
				set_value(cmd_master, pos, cmd);
				pos++;
			}
		}
		else if (cmd->type == CMD_OR)
		{
			if (pos == 0)
			{
				set_value(cmd_master, pos, cmd_prev);
				pos++;
			}
			if (get_or_cmd(cmd, args, &i, &cmd_prev))
			{
				set_value(cmd_master, pos, cmd);
				pos++;
			}
		}
		else if (cmd->type == CMD_PARENTHESIS_OPEN)
		{
			get_seq_cmd(args, cmd_master, &i, &pos);
		}
		else
		{
			cmd_prev = cmd;
		}
	}

	return (cmd_master);
}



int main() {
	//int i;
	//int pos;
	//t_ast_node *cmd_prev;
	//t_ast_node *cmd;
	//t_ast_node *new_cmd2;
	//t_ast_node *new_cmd3;
	//t_ast_node *new_cmd4;
	t_dynamic_array	*cmd_master;
	t_dynamic_array *tokens;
	
	//tokens = init_dynamic_array_malloc(20, NULL);
	//set_value(tokens, 0, init_token(TOKEN_TEXT, "ls", 0, 2));
	//set_value(tokens, 1, init_token(TOKEN_TEXT, "-l", 0, 2));
	//set_value(tokens, 2, init_token(TOKEN_AND, "&&", 0, 2));
	//set_value(tokens, 3, init_token(TOKEN_TEXT, "echo", 0, 4));
	//set_value(tokens, 4, init_token(TOKEN_VAR_TEXT, "hello", 0, 5));
	//set_value(tokens, 5, init_token(TOKEN_AND, "&&", 0, 2));
	//set_value(tokens, 6, init_token(TOKEN_TEXT, "cat", 0, 3));
	//set_value(tokens, 7, init_token(TOKEN_LITERAL_TEXT, "file.txt", 0, 8));
	//set_value(tokens, 8, init_token(TOKEN_PIPE, "|", 0, 1));
	//set_value(tokens, 9, init_token(TOKEN_LITERAL_TEXT, "output.txt", 0, 10));
	//set_value(tokens, 10, init_token(TOKEN_AND, "&&", 0, 2));
	//set_value(tokens, 11, init_token(TOKEN_TEXT, "echo", 0, 4));
	//set_value(tokens, 12, init_token(TOKEN_LITERAL_TEXT, "jojo", 0, 4));
	//set_value(tokens, 13, init_token(TOKEN_OR, "||", 0, 2));
	//set_value(tokens, 14, init_token(TOKEN_TEXT, "echo", 0, 4));
	//set_value(tokens, 15, init_token(TOKEN_LITERAL_TEXT, "tata", 0, 4));
	// ls -l && echo "hello" && cat file.txt | output.txt && echo "jojo" || echo "tata"
	t_parse_status status;
	t_lexer_args args;
	
	//args = init_lexer_args("true || (echo 'A' && echo 'B')");
	//args = init_lexer_args("ls -l && echo 'hello' && cat file.txt | output.txt && echo 'jojo' || echo 'tata'");
	//args = init_lexer_args("ls -l && echo 'hello' && cat file.txt | output.txt | momo.txt && echo 'jojo' || echo 'tata'");
	//args = init_lexer_args("dzidziu\"$PATH\""); // ajouter les espaces au token
	//args = init_lexer_args("echo \"bonjour\" && ( echo \"jojo\" && echo \"pipi\" ) || cat file.txt | output.txt | momo.txt | toto.txt | jiji.txt && echo \"jojo\" && echo \"toto\"");
	//args = init_lexer_args("echo \"bonjour\" && ( echo \"jojo\" || ( echo \"lord\" && echo \"dart\" ) && (echo \"pipi\") )" );
	args = init_lexer_args("( echo \"bonjour\" &&  echo \"jojo\" )");
	args = init_lexer_args("(ls | cat)|cat|(g || ls)|wc");
	status = lexer(&args);
	if (status != COMMAND_VALID)
	{
		printf("Error: %s\n", (&args)->error);
		return (0);
	}
	print_tokens(&(&args)->tokens);

	tokens = &args.tokens;
	cmd_master = get_cmd_master((t_get_cmd_master){tokens, 0, tokens->count - 1});
	print_ast_json_wrapper(cmd_master);
















	// FONCTIONNEL
	

	//i = 0;
	//pos = 0;
	//new_cmd = get_cmd(tokens, &i);
	//set_value(cmd, pos, new_cmd);
	//pos++;
	//while (i < tokens->count - 1)
	//{
	//	new_cmd = get_cmd(tokens, &i);

	//	if (new_cmd->type != CMD)
	//	{
	//		new_cmd2 = get_cmd(tokens, &i);




	//		//new_cmd3 = get_cmd(tokens, &i);
	//		//if (new_cmd3 && new_cmd3->type == CMD_PIPE)
	//		//{
	//		//	add_child(new_cmd3, new_cmd2);
	//		//	new_cmd4 = get_cmd(tokens, &i);
	//		//	add_child(new_cmd3, new_cmd4);
	//		//	add_child(new_cmd, new_cmd3);
	//		//}
	//		//else if (new_cmd3 && new_cmd3->type == CMD_PARENTHESIS_OPEN)
	//		//{

	//		//}
	//		//else if (new_cmd3 && new_cmd3->type == CMD_PARENTHESIS_CLOSE)
	//		//{
				
	//		//}
	//		//else
	//		//{
	//		//	if (new_cmd3)
	//		//		i--;
	//			add_child(new_cmd, new_cmd2);
	//		//}
	//	}
	//	set_value(cmd, pos, new_cmd);
	//	pos++;
	//}
	//print_ast_json_wrapper(cmd);
    return 0;
}

//cc srcs/ast_builder/ast_builder.c libs/libft/srcs/**/*.c srcs/structs/**/*.c srcs/lexer/*.c -I includes -I libs/libft/includes












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