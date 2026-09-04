/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 00:00:00 by dancel            #+#    #+#             */
/*   Updated: 2026/09/04 00:00:00 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc		g_malloc;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	split_block(t_block *block, size_t size)
{
	t_block	*new_block;

	if (block->size < size + sizeof(t_block) + 16)
		return ;
	new_block = (t_block *)((char *)block + sizeof(t_block) + size);
	new_block->size = block->size - size - sizeof(t_block);
	new_block->free = 1;
	new_block->next = block->next;
	block->size = size;
	block->next = new_block;
}

static t_block	*find_free_block(t_zone *zones, size_t size)
{
	t_zone	*zone;
	t_block	*block;

	zone = zones;
	while (zone)
	{
		block = zone->blocks;
		while (block)
		{
			if (block->free && block->size >= size)
				return (block);
			block = block->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

static t_block	*get_block(t_zone **list, size_t zone_capacity, size_t size)
{
	t_block	*block;
	t_zone	*zone;

	block = find_free_block(*list, size);
	if (block)
		return (block);

	zone = new_zone(zone_capacity);
	if (!zone)
		return (NULL);

	zone->next = *list;
	*list = zone;
	return (zone->blocks);
}

void	*malloc_impl(size_t size)
{
	size_t	aligned;
	t_block	*block;

	if (size == 0)
		size = 1;
	aligned = align16(size);
	if (aligned < size)
		return (NULL);
	if (aligned <= TINY_MAX)
		block = get_block(&g_malloc.tiny, 100 * TINY_MAX + 99 * sizeof(t_block), aligned);
	else if (aligned <= SMALL_MAX)
		block = get_block(&g_malloc.small, 100 * SMALL_MAX + 99 * sizeof(t_block), aligned);
	else
		block = get_block(&g_malloc.large, aligned, aligned);
	if (!block)
		return (NULL);
	split_block(block, aligned);
	block->free = 0;
	return ((char *)block + sizeof(t_block));
}

void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = malloc_impl(size);
	record_history('M', ptr, size);
	pthread_mutex_unlock(&g_mutex);
	debug_malloc(size, ptr);
	return (ptr);
}
