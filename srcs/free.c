/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 00:00:00 by dancel            #+#    #+#             */
/*   Updated: 2026/09/08 19:07:48 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*block_prev(t_zone *zone, t_block *block)
{
	t_block	*cur;

	cur = zone->blocks;
	while (cur)
	{
		if (cur->next == block)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

static void	free_from(t_zone **list, t_zone *prev_zone, t_zone *zone, t_block *block, int reclaim_if_empty)
{
	t_block	*prev_block;

	block->free = 1;
	merge_next(block);
	prev_block = block_prev(zone, block);
	if (prev_block && prev_block->free)
	{
		merge_next(prev_block);
		block = prev_block;
	}
	if (reclaim_if_empty && block == zone->blocks && !block->next)
	{
		if (prev_zone)
			prev_zone->next = zone->next;
		else
			*list = zone->next;
		munmap(zone, zone->size);
	}
}

static t_zone	*find_zone(t_zone *zones, t_block *block, t_zone **prev_zone)
{
	t_zone	*zone;
	t_zone	*prev;

	zone = zones;
	prev = NULL;
	while (zone)
	{
		if ((char *)block >= (char *)zone && (char *)block < (char *)zone + zone->size)
		{
			*prev_zone = prev;
			return (zone);
		}
		prev = zone;
		zone = zone->next;
	}
	return (NULL);
}

void	free_impl(void *ptr)
{
	t_block	*block;
	t_zone	*zone;
	t_zone	*prev_zone;

	if (!ptr)
		return ;
	block = (t_block *)((char *)ptr - sizeof(t_block));
	zone = find_zone(g_malloc.tiny, block, &prev_zone);
	if (zone)
		return (free_from(&g_malloc.tiny, prev_zone, zone, block, 0));
	zone = find_zone(g_malloc.small, block, &prev_zone);
	if (zone)
		return (free_from(&g_malloc.small, prev_zone, zone, block, 0));
	zone = find_zone(g_malloc.large, block, &prev_zone);
	if (zone)
		return (free_from(&g_malloc.large, prev_zone, zone, block, 1));
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	free_impl(ptr);
	record_history('F', ptr, 0);
	pthread_mutex_unlock(&g_mutex);
	debug_free(ptr);
}
