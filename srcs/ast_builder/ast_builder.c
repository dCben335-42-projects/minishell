/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:05:23 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/20 19:28:03 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_builder.h"
#include <stdlib.h>
#include "config.h"
#include "libft.h"



///**
// * @brief Parcourt l'AST et encapsule les paires CMD_PARENTHESIS + CMD_BASE
// * dans un nouveau noeud parent CMD_SUB_REDIR.
// *
// * @param root Le noeud racine de l'AST à analyser et corriger.
// */
//void	hotfix_subredir(t_ast *root)
//{
//	if (!root || !root->content || root->child_count < 2 || root->type == CMD_SUB_REDIR)
//		return;

//	t_dynarray	*children = (t_dynarray *)root->content;
//	t_uint		i = 0;

//	while (i + 1 < children->count)
//	{
//		t_ast *child1 = get_dynarray_value(children, i);
//		t_ast *child2 = get_dynarray_value(children, i + 1);

//		if (child1 && child2
//			&& child1->type == CMD_PARENTHESIS
//			&& child2->type == CMD_BASE)
//		{
//			t_ast *subredir = init_ast_node(CMD_SUB_REDIR, NULL);
//			if (!subredir)
//				return;

//			t_ast_ctx ctx = { .has_malloc_error = FALSE };

//			child1->parent = subredir;
//			add_child(subredir, &child1, &ctx);
//			child2->parent = subredir;
//			child2->next = NULL;
//			add_child(subredir, &child2, &ctx);
//			if (ctx.has_malloc_error)
//			{
//				destroy_ast(subredir);
//				return;
//			}
//			printf("SUB_REDIR_CONTENT:\n");
//			print_ast(subredir->content);
//			remove_range_dynarray(children, i + 1, i + 1);
//			print_ast(children);
//			root->child_count -= 1;
//			set_dynarray_value(children, i, subredir, TRUE);
//			print_ast(children);
//		}
//		else
//		{
//			hotfix_subredir(child1);
//			i++;
//		}
//	}
//}



/**
 * @brief Parcourt l'AST et encapsule les paires CMD_PARENTHESIS + CMD_BASE
 * dans un nouveau noeud parent CMD_SUB_REDIR.
 *
 * @param root Le noeud racine de l'AST à analyser et corriger.
 */
void	hotfix_subredir(t_ast *root)
{
	if (!root || !root->content || root->child_count < 2 || root->type == CMD_SUB_REDIR)
		return;

	t_dynarray	*children = (t_dynarray *)root->content;
	t_uint		i = 0;

	while (i + 1 < children->count)
	{
		t_ast *child1 = get_dynarray_value(children, i);
		t_ast *child2 = get_dynarray_value(children, i + 1);

		if (child1 && child2
			&& child1->type == CMD_PARENTHESIS
			&& child2->type == CMD_BASE)
		{
			t_ast *subredir = init_ast_node(CMD_SUB_REDIR, NULL);
			if (!subredir)
				return;

			t_ast_ctx ctx = { .has_malloc_error = FALSE };

			child1->parent = subredir;
			add_child(subredir, &child1, &ctx);
			child2->parent = subredir;
			child2->next = NULL;
			add_child(subredir, &child2, &ctx);
			if (ctx.has_malloc_error)
			{
				destroy_ast(subredir);
				return;
			}
			printf("SUB_REDIR_CONTENT:\n");
			print_ast(subredir->content);
			remove_range_dynarray(children, i + 1, i + 1);
			print_ast(children);
			root->child_count -= 1;
			set_dynarray_value(children, i, subredir, TRUE);
			print_ast(children);
		}
		else
		{
			hotfix_subredir(child1);
			i++;
		}
	}
}


void hotfix_pipe(t_ast *node, t_uint *index, t_ast	*master_node)
{
	t_ast *mast;
	
	printf("hotfix_pipe: node type = %d, index = %u\n", node->type, *index);
	if (node->type == CMD_PARENTHESIS && node->next && node->next->type == CMD_PIPE)
	{
		printf("___________________________");
		if (node->parent)
			mast = node->parent;
		mast = master_node;
		print_ast(master_node->content);
		printf("___________________________");
		t_ast *node2 = get_dynarray_value((t_dynarray *)node->next->content, 0);
		print_ast(node2->content);
		t_ast *subredir = init_ast_node(CMD_SUB_REDIR, NULL);
		if (!subredir)
			return;
		t_ast_ctx ctx = { .has_malloc_error = FALSE };
		node->parent = subredir;
		add_child(subredir, &node, &ctx);
		node2->parent = subredir;
		node2->next = NULL;
		add_child(subredir, &node2, &ctx);
		printf("SUB_REDIR_CONTENT:\n");
		print_ast(subredir->content);
		printf("MASTER_NODE:\n");
		printf("master node type = %d\n", mast->type);
		print_ast(mast->content);
		remove_range_dynarray(mast->content, *index, *index);
		printf("After remove_range_dynarray:\n");
		print_ast(mast->content);
		mast->child_count -= 1;
		(*index)--;
		printf("After dzdzd:\n");
		set_dynarray_value((t_dynarray *)node->next->content, 0, subredir, FALSE);
		printf("After dzdzd:\n");
		print_ast(mast->content);
	}
}


void	traverse_ast(t_ast *node, t_uint *index, t_ast *master_node)
{
	if (!node)
		return;

	// Appliquer la fonction de rappel au nœud courant
	hotfix_pipe(node, index, master_node);

	// Si ce nœud a des enfants, on les parcourt récursivement
	if (node->content && (node->type != CMD_TEXT)) // On suppose que WORD et TEXT n'ont pas de children dynarray
	{
		t_dynarray *children = (t_dynarray *)node->content;
		for (t_uint i = 0; i < children->count; ++i)
		{
			t_ast *child = get_dynarray_value(children, i);
			if (child)
				traverse_ast(child, &i, master_node);
		}
	}
}

/**
 * 
 * @brief Builds the AST from the given tokens.
 * This function initializes the master node of the AST and
 * calls the command master function to populate it.
 * 
 * @param tokens Dynamic array of tokens.
 * 
 * @note The master node is initialized with the type CMD_SEQ.
 * 
 * @return t_ast* Pointer to the root of the AST or NULL on malloc error.
 * 
*/
t_ast	*ast_builder(t_dynarray *tokens)
{
	t_ast_ctx	ast_glbctx;
	t_ast		*master_node;

	master_node = init_ast_node(CMD_SEQ, NULL);
	if (!master_node)
	{
		ft_putendl_fd(ERR_MALLOC, 2);
		return (NULL);
	}
	ast_glbctx = init_ast_glbctx(
			tokens,
			0,
			tokens->count - 1,
			master_node);
	add_master_cmds(&ast_glbctx);
	if (ast_glbctx.has_malloc_error)
		ft_putendl_fd(ERR_MALLOC, 2);
	if (ast_glbctx.local.cmd_master && ast_glbctx.has_malloc_error)
		return (destroy_ast(ast_glbctx.local.cmd_master));
	//hotfix_subredir(ast_glbctx.local.cmd_master);
	traverse_ast(ast_glbctx.local.cmd_master, &ast_glbctx.start, ast_glbctx.local.cmd_master);
	return (ast_glbctx.local.cmd_master);
}
