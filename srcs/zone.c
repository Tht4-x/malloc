#include "malloc.h"

size_t	align16(size_t size)
{
	return ((size + 15) & ~((size_t)15));
}

static size_t	zone_total_size(size_t capacity)
{
	size_t	needed;
	size_t	page;

	needed = sizeof(t_zone) + sizeof(t_block) + capacity;
	page = (size_t)sysconf(_SC_PAGESIZE);
	return (((needed + page - 1) / page) * page);
}

t_zone	*new_zone(size_t capacity)
{
	size_t	total;
	t_zone	*zone;

	total = zone_total_size(capacity);
	zone = mmap(NULL, total, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (zone == MAP_FAILED)
		return (NULL);
	zone->next = NULL;
	zone->size = total;
	zone->blocks = (t_block *)((char *)zone + sizeof(t_zone));
	zone->blocks->size = total - sizeof(t_zone) - sizeof(t_block);
	zone->blocks->free = 1;
	zone->blocks->next = NULL;
	return (zone);
}
