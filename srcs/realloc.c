/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 00:00:00 by dancel            #+#    #+#             */
/*   Updated: 2026/09/04 00:00:00 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	merge_next(t_block *block)
{
	if (block->next && block->next->free)
	{
		block->size += sizeof(t_block) + block->next->size;
		block->next = block->next->next;
	}
}

static void	*realloc_impl(void *ptr, size_t size)
{
	t_block	*block;
	void	*new_ptr;
	size_t	aligned;
	size_t	copy_size;

	if (!ptr)
		return (malloc_impl(size));
	if (size == 0)
		return (free_impl(ptr), NULL);
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
	new_ptr = malloc_impl(size);
	if (!new_ptr)
		return (NULL);
	copy_size = block->size;
	if (copy_size > size)
		copy_size = size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free_impl(ptr);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*result;

	pthread_mutex_lock(&g_mutex);
	result = realloc_impl(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	debug_realloc(ptr, size, result);
	return (result);
}
