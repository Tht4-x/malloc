#include "malloc.h"

# define DUMP_MAX 64

static void	put_byte_hex(unsigned char byte, int fd)
{
	static const char	hex[] = "0123456789abcdef";

	ft_putchar_fd(hex[byte >> 4], fd);
	ft_putchar_fd(hex[byte & 0xf], fd);
}

static void	dump_line(unsigned char *data, size_t offset, size_t line_len)
{
	size_t	j;

	ft_printf("    %zu: ", offset);
	j = 0;
	while (j < 16)
	{
		if (j < line_len)
			put_byte_hex(data[offset + j], 1);
		else
			ft_putstr_fd("  ", 1);
		ft_putchar_fd(' ', 1);
		j++;
	}
	ft_putstr_fd(" |", 1);
	j = 0;
	while (j < line_len)
	{
		if (data[offset + j] >= 32 && data[offset + j] < 127)
			ft_putchar_fd(data[offset + j], 1);
		else
			ft_putchar_fd('.', 1);
		j++;
	}
	ft_putstr_fd("|\n", 1);
}

static void	hexdump_block(t_block *block)
{
	unsigned char	*data;
	size_t			shown;
	size_t			i;
	size_t			line_len;

	data = (unsigned char *)block + sizeof(t_block);
	shown = block->size;
	if (shown > DUMP_MAX)
		shown = DUMP_MAX;
	i = 0;
	while (i < shown)
	{
		line_len = shown - i;
		if (line_len > 16)
			line_len = 16;
		dump_line(data, i, line_len);
		i += 16;
	}
	if (block->size > DUMP_MAX)
		ft_printf("    ... (%zu more bytes)\n", block->size - DUMP_MAX);
}

static void	show_zone_ex(t_zone *zone, char *label)
{
	t_block	*block;

	while (zone)
	{
		ft_printf("%s : %p\n", label, (void *)zone);
		block = zone->blocks;
		while (block)
		{
			if (!block->free)
			{
				ft_printf("%p - %p : %zu bytes\n", (void *)((char *)block + sizeof(t_block)), (void *)((char *)block + sizeof(t_block) + block->size), block->size);
				hexdump_block(block);
			}
			block = block->next;
		}
		zone = zone->next;
	}
}

void	show_alloc_mem_ex(void)
{
	pthread_mutex_lock(&g_mutex);
	show_zone_ex(g_malloc.tiny, "TINY");
	show_zone_ex(g_malloc.small, "SMALL");
	show_zone_ex(g_malloc.large, "LARGE");
	pthread_mutex_unlock(&g_mutex);
}
