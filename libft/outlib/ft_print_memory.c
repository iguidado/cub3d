/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 22:59:54 by iguidado          #+#    #+#             */
/*   Updated: 2020/02/07 23:03:36 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_print_addrhex_n(unsigned long nbr, unsigned int n)
{
	if (n)
		ft_print_addrhex_n(nbr / 16, n - 1);
	write(1, &"0123456789abcdef"[nbr % 16], 1);
}

static void	ft_print_strhex_n(unsigned char *str, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i < 16)
	{
		if (i >= n)
			write(1, "  ", 2);
		else
		{
			write(1, &"0123456789abcdef"[(str[i]) / 16], 1);
			write(1, &"0123456789abcdef"[(str[i]) % 16], 1);
		}
		if (i % 2)
			write(1, " ", 1);
		i++;
	}
}

static void	ft_printmem_str_format(unsigned char *str, unsigned int size)
{
	while (size)
	{
		if (*str < 32 || *str > 126)
			write(1, ".", 1);
		else
			write(1, str, 1);
		str++;
		size--;
	}
}

void		*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int i;
	unsigned int str_len;

	i = 0;
	while (i < size)
	{
		str_len = ((size - i) < 16 ? (size - i) : 16);
		ft_print_addrhex_n((long)&addr[i], 16);
		write(1, " :", 2);
		ft_print_strhex_n((unsigned char *)&addr[i], str_len);
		ft_printmem_str_format((unsigned char *)&addr[i], str_len);
		write(1, "\n", 1);
		i = i + 16;
	}
	return (addr);
}

/*
**	int	main(void)
**	{
**		ft_print_memory(&"Hello World !", 40);
**		return (0);
**	}
*/
