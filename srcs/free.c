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

static void	merge_next(t_block *block)
{
	if (block->next && block->next->free)
	{
		block->size += sizeof(t_block) + block->next->size;
		block->next = block->next->next;
	}
}

static void	free_from(t_zone **list, t_block *block, int reclaim_if_empty)
{
	t_zone	*prev_zone;
	t_zone	*zone;
	t_block	*prev_block;

	zone = find_zone(*list, block, &prev_zone);
	if (!zone)
		return ;
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
			if (prev_zone)
				*prev_zone = prev;
			return (zone);
		}
		prev = zone;
		zone = zone->next;
	}
	return (NULL);
}

void	free(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	block = (t_block *)((char *)ptr - sizeof(t_block));
	
	if (find_zone(g_malloc.tiny, block, NULL))
		free_from(&g_malloc.tiny, block, 0);
	else if (find_zone(g_malloc.small, block, NULL))
		free_from(&g_malloc.small, block, 0);
	else if (find_zone(g_malloc.large, block, NULL))
		free_from(&g_malloc.large, block, 1);
}
