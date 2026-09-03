#include "libft.h"

int	ft_putptr(void *ptr)
{
	unsigned long long	ull;

	ull = (unsigned long long)ptr;
	if (!ull)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	return (ft_puthex(ull, 'x') + 2);
}
