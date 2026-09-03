#include "libft.h"

int	ft_putnbr(int n)
{
	char	c;
	int		len;
	long	num;

	len = 0;
	num = n;
	if (num < 0)
	{
		len += write(1, "-", 1);
		num = -num;
	}
	if (num >= 10)
		len += ft_putnbr(num / 10);
	c = (num % 10) + '0';
	len += write(1, &c, 1);
	return (len);
}
