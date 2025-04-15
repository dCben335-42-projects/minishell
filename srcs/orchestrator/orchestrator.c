#include "ast.h"
#include "orchestrator.h"


void	execute_cmd_base()
{
	return ;
}

void	execute_cmd_and()
{
	return ;
}

void	execute_cmd_or()
{
	return ;
}

void	execute_cmd_pipe()
{
	return ;
}

void	orchestrator(t_dynamic_array *master_node_childs)
{
	t_ast_node	*master_node;
	t_ast_node	*cmd;
	
	master_node = init_node(CMD_SEQ, NULL);
	add_childs(master_node, master_node_childs);
	cmd = find_next_cmd(master_node);
	printf("--------------------\n");
	while (cmd)
	{
		print_ast_json_wrapper(cmd->content);
		if (cmd->parent == NULL)
			execute_cmd_base();
		if (cmd->parent->type == CMD_AND)
			execute_cmd_and();
		if (cmd->parent->type == CMD_OR)
			execute_cmd_or();
		if (cmd->parent->type == CMD_PIPE)
			execute_cmd_pipe();
		cmd = find_next_cmd(master_node);
	}





	//print_ast_json_wrapper(find_next_cmd(master_node)->content);
	//print_ast_json_wrapper(find_next_cmd(master_node)->content);
	//print_ast_json_wrapper(find_next_cmd(master_node)->content);
	//print_ast_json_wrapper(find_next_cmd(master_node)->content);
}

// ( ( ( echo 'salut' ) ) && echo 'bonjour' ) | echo bar | echo "sa va"