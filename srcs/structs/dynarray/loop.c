#include "dynarray.h"
#include "shell.h"

void	loop_dynarray(t_dynarray *arr, t_shell *shell, void *(*f)(t_shell *, void *))
{
	t_uint	i;

	i = 0;
	while (i < arr->count)
	{
		f(shell, arr->data[i]);
		i++;
	}
}