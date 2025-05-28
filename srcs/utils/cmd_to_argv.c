

#include "libft_tree.h"
#include "libft.h"
#include "struct_dynarray.h"
#include "stdio.h"
#include "cmd_expand.h"
#include "struct_shell.h"

static void	cleanup_args(t_dynarray *arr)
{
	t_uint	i;
	t_uint	j;
	t_uint	count;
	char	*str;
	
	if (!arr || !arr->data)
		return;
	i = 0;
	j = 0;
	count = arr->count;
	while (i < count)
	{
		str = get_dynarray_value(arr, i);
		if (str && *str)
			arr->data[j++] = arr->data[i];
		else
			arr->destroyer(arr->data[i]); 
		i++;
	}
	arr->count = j;
	while (j < count)
		arr->data[j++] = NULL;
}


static void	skip_redirection(t_uint *i, t_uint count, t_dynarray *arr)
{
	t_ast_node	*node;

	while (*i < count)
	{
		node = (t_ast_node *)get_dynarray_value(arr, *i);
		if (node->type == CMD_WORD)
			break ;
		(*i)++;
	}
}

t_dynarray	*cmd_to_argv(t_shell *shell, t_dynarray *arr, t_dynarray *argv)
{
	t_ast_node	*node;
	t_uint		i;

	if (!argv->data)
		return (NULL);
	i = 0;
	while (i < arr->count)
	{
		skip_redirection(&i, arr->count, arr);
		node = (t_ast_node *)get_dynarray_value(arr, i);
		if (node && !expand_word(shell, node->content, argv))
			return (destroy_dynarray(argv));
		i++;
	}
	cleanup_args(argv);
	return (argv);
}
