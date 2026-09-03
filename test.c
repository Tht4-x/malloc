#include "malloc.h"

int	main(void)
{
	void	*tiny_1, *tiny_2, *tiny_3;
	void	*small_1, *small_2;
	void	*large_1, *large_2;

	tiny_1 = malloc(64);
	tiny_2 = malloc(60);
	tiny_3 = malloc(12);
	small_1 = malloc(510);
	large_1 = malloc(5000);
	large_2 = malloc(2000);

	show_alloc_mem();
	ft_printf("\n");

	tiny_1 = realloc(tiny_1, 0); 
	tiny_2 = realloc(tiny_2, 50);
	tiny_3 = realloc(tiny_3, 110);
	small_2 = realloc(NULL, 400);
	large_2 = realloc(large_2, 2050);
	show_alloc_mem();
	ft_printf("\n");

	free(tiny_1);
	free(tiny_2);
	free(tiny_3);
	free(small_1);
	free(small_2);
	free(large_1);
	free(large_2);
	show_alloc_mem();
	return (0);
}
