#ifndef STRUCT_POINTER_H
# define STRUCT_POINTER_H

# include "types.h"


typedef struct t_pointer
{
	t_bool		is_malloc;
	t_bool		has_malloc_error;
	void		*pointer;
}	t_pointer;

t_pointer	init_pointer(void *pointer, t_bool is_malloc, t_bool has_malloc_error);

#endif