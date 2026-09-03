#include "libft.h"

int	ft_puthex(unsigned long long num, char format)
{
	char	*hex;
	int		len;

	len = 0;
	if (format == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (num >= 16)
		len += ft_puthex(num / 16, format);
	len += write(1, &hex[num % 16], 1);
	return (len);
}
