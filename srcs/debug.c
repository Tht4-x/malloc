/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 00:00:00 by dancel            #+#    #+#             */
/*   Updated: 2026/09/04 00:00:00 by dancel           ###   ########.fr       */
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
