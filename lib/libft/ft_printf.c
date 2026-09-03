#include "libft.h"

static int	ft_printf_format(const char *format, int i, va_list args)
{
	int	len;

	len = 0;
	if (format[i] == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (format[i] == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (format[i] == 'p')
		len += ft_putptr(va_arg(args, void *));
	else if (format[i] == 'd' || format[i] == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (format[i] == 'u')
		len += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (format[i] == 'x' || format[i] == 'X')
		len += ft_puthex(va_arg(args, unsigned int), format[i]);
	else if (format[i] == '%')
		len += ft_putchar('%');
	else
	{
		len += ft_putchar('%');
		len += ft_putchar(format[i]);
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(args, format);
	if (format == NULL)
		return (va_end(args), -1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			len += ft_printf_format(format, i, args);
		}
		else if (format[i] == '%' && format[i + 1] == '\0')
			len = -1;
		else
			len += ft_putchar(format[i]);
		i++;
	}
	return (va_end(args), len);
}
