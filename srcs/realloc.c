#include "malloc.h"

void	merge_next(t_block *block)
{
	if (block->next && block->next->free)
	{
		block->size += sizeof(t_block) + block->next->size;
		block->next = block->next->next;
	}
}

void	*realloc(void *ptr, size_t size) 
{
	t_block	*block;
	void	*new_ptr;
	size_t	aligned;
	size_t	copy_size;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
		return (free(ptr), NULL);

	aligned = align16(size);
	if (aligned < size)
		return (NULL);

	block = (t_block *)((char *)ptr - sizeof(t_block));
	if (aligned <= block->size)
		return (ptr);

	if (block->next && block->next->free && block->size + sizeof(t_block) + block->next->size >= aligned)
	{
		merge_next(block);
		split_block(block, aligned);
		return (ptr);
	}

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
		
	copy_size = block->size;
	if (copy_size > size)
		copy_size = size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
