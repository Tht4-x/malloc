/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 00:00:00 by dancel            #+#    #+#             */
/*   Updated: 2026/09/04 18:04:00 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(void)
{
	void	*tiny_1, *tiny_2, *tiny_3;
	void	*small_1, *small_2;
	void	*large_1, *large_2;

	tiny_1 = malloc(64);
	ft_memcpy(tiny_1, "Hello", 6);
	tiny_2 = malloc(60);
	ft_memcpy(tiny_2, "world", 6);
	tiny_3 = malloc(12);
	small_1 = malloc(510);
	large_1 = malloc(5000);
	large_2 = malloc(2000);
	if (!getenv("MALLOC_DEBUG"))
		show_alloc_mem();	
	else
		show_alloc_mem_ex();
	ft_printf("\n");

	tiny_1 = realloc(tiny_1, 0); 
	tiny_2 = realloc(tiny_2, 50);
	tiny_3 = realloc(tiny_3, 110);
	small_2 = realloc(NULL, 400);
	large_2 = realloc(large_2, 2050);
	if (!getenv("MALLOC_DEBUG"))
		show_alloc_mem();	
	else
		show_alloc_mem_ex();
	ft_printf("\n");

	free(tiny_1);
	free(tiny_2);
	free(tiny_3);
	free(small_1);
	free(small_2);
	free(large_1);
	free(large_2);
	if (!getenv("MALLOC_DEBUG"))
		show_alloc_mem();	
	else
		show_alloc_mem_ex();
		
	ft_printf("\n");
	if (getenv("MALLOC_DEBUG"))
		show_alloc_history();
	return (0);
}
