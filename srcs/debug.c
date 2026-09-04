/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 00:00:00 by dancel            #+#    #+#             */
/*   Updated: 2026/09/04 17:48:55 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	debug_malloc(size_t size, void *ptr)
{
	if (!getenv("MALLOC_DEBUG"))
		return ;
	ft_dprintf(2, "[malloc] size=%zu -> %p\n", size, ptr);
}

void	debug_free(void *ptr)
{
	if (!getenv("MALLOC_DEBUG"))
		return ;
	ft_dprintf(2, "[free] %p\n", ptr);
}

void	debug_realloc(void *old, size_t size, void *new_ptr)
{
	if (!getenv("MALLOC_DEBUG"))
		return ;
	ft_dprintf(2, "[realloc] %p size=%zu -> %p\n", old, size, new_ptr);
}

void	record_history(char action, void *ptr, size_t size)
{
	size_t	i;

	i = g_malloc.history_count % HISTORY_MAX;
	g_malloc.history[i].action = action;
	g_malloc.history[i].ptr = ptr;
	g_malloc.history[i].size = size;
	g_malloc.history_count++;
}

void	show_alloc_history(void)
{
	size_t		i;
	size_t		count;
	t_history	*h;

	pthread_mutex_lock(&g_mutex);
	count = g_malloc.history_count;
	if (count > HISTORY_MAX)
		count = HISTORY_MAX;
	i = 0;
	while (i < count)
	{
		h = &g_malloc.history[i];
		if (h->action == 'M')
			ft_printf("malloc(%zu) -> %p\n", h->size, h->ptr);
		else if (h->action == 'F')
			ft_printf("free(%p)\n", h->ptr);
		else
			ft_printf("realloc(size=%zu) -> %p\n", h->size, h->ptr);
		i++;
	}
	ft_printf("Total events recorded: %zu\n", g_malloc.history_count);
	pthread_mutex_unlock(&g_mutex);
}
