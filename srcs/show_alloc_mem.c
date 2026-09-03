#include "malloc.h"

static size_t	show_zone(t_zone *zone, char *label)
{
	t_block	*block;
	size_t	total;

	total = 0;
	while (zone)
	{
		ft_printf("%s : %p\n", label, (void *)zone);
		block = zone->blocks;
		while (block)
		{
			if (!block->free)
			{
				ft_printf("%p - %p : %u bytes\n", (void *)((char *)block + sizeof(t_block)), (void *)((char *)block + sizeof(t_block) + block->size), (unsigned int)block->size);
				total += block->size;
			}
			block = block->next;
		}
		zone = zone->next;
	}
	return (total);
}

void	show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	total += show_zone(g_malloc.tiny, "TINY");
	total += show_zone(g_malloc.small, "SMALL");
	total += show_zone(g_malloc.large, "LARGE");
	ft_printf("Total : %u bytes\n", (unsigned int)total);
}
