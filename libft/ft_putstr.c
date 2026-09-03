#include "libft.h"

int	ft_putstr(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!str)
		str = "(null)";
	while (str[i])
		i++;
	len += write(1, str, i);
	return (len);
}
