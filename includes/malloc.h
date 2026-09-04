/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 00:00:00 by dancel            #+#    #+#             */
/*   Updated: 2026/09/04 00:00:00 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include <stddef.h>
# include <pthread.h>
# include "libft.h"

# define TINY_MAX	128
# define SMALL_MAX	1024
# define HISTORY_MAX	200

typedef struct s_history
{
	char	action;
	void	*ptr;
	size_t	size;
}			t_history;

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
	t_zone		*tiny;
	t_zone		*small;
	t_zone		*large;
	t_history	history[HISTORY_MAX];
	size_t		history_count;
}					t_malloc;

extern t_malloc			g_malloc;
extern pthread_mutex_t	g_mutex;

size_t	align16(size_t size);
t_zone	*new_zone(size_t capacity);
void	merge_next(t_block *block);
void	split_block(t_block *block, size_t size);
void	show_alloc_mem(void);
void	show_alloc_mem_ex(void);
void	*malloc_impl(size_t size);
void	free_impl(void *ptr);
void	debug_malloc(size_t size, void *ptr);
void	debug_free(void *ptr);
void	debug_realloc(void *old, size_t size, void *new_ptr);
void	record_history(char action, void *ptr, size_t size);
void	show_alloc_history(void);

#endif
