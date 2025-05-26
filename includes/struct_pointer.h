#ifndef STRUCT_POINTER_H
# define STRUCT_POINTER_H

# include "types.h"

/**
 * @brief Structure to manage pointers and their allocation status.
 * 
 * This structure is used to keep track of whether a pointer was
 * dynamically allocated (malloc) or not. It also includes a flag
 * to indicate if there was an error during the allocation process.
 * 
 * @param is_malloc Indicates if the pointer was allocated with malloc.
 * @param has_malloc_error Indicates if there was an error during allocation.
 * @param pointer The pointer to the allocated memory.
 * 
 * @note This structure is meant to be used directly in the stack 
 * without allocating it on the heap.
 * 
 */
typedef struct s_ptr
{
	t_bool		is_malloc;
	t_bool		has_malloc_error;
	void		*p;
}	t_ptr;

t_ptr	init_pointer(void *pointer, t_bool is_malloc);

#endif