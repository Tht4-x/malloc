#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include <stddef.h>
# include "libft.h"

# define TINY_MAX	128
# define SMALL_MAX	1024

typedef struct s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;
}					t_block;

typedef struct s_zone
{
	size_t			size;
	t_block			*blocks;
	struct s_zone	*next;
}					t_zone;

typedef struct s_malloc
{
	t_zone	*tiny;
	t_zone	*small;
	t_zone	*large;
}					t_malloc;

extern t_malloc		g_malloc;

size_t	align16(size_t size);
t_zone	*new_zone(size_t capacity);

#endif
