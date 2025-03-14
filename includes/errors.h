#ifndef ERRORS_H
# define ERRORS_H

# include <stdlib.h>
# include <stdio.h>
# include "types.h"

# include <stdint.h>

void	*p_ptr(void *data, const char *msg);
t_bool	p_int(int data, int error_value, const char *msg);
void	*s_ptr(void *data, const char *msg);


#endif