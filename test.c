#include "malloc.h"

int	main(void)
{
	void	*tiny;
	void	*small;
	void	*large;

	tiny = malloc(64);
	small = malloc(512);
	large = malloc(5000);
	(void)tiny;
	(void)small;
	(void)large;
	show_alloc_mem();
	free(tiny);
	free(small);
	free(large);
	show_alloc_mem();
	return (0);
}
