/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 22:40:54 by iguidado          #+#    #+#             */
/*   Updated: 2020/02/07 22:59:36 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_printhex(unsigned char c)
{
	write(1, "\\", 1);
	write(1, &"0123456789abcdef"[c / 16], 1);
	write(1, &"0123456789abcdef"[c % 16], 1);
}

void		ft_putstr_non_printable(char *str)
{
	unsigned char c;

	while (*str)
	{
		c = (unsigned char)*str;
		if (c < 32 || c > 126)
			ft_printhex(c);
		else
			write(1, &c, 1);
		str++;
	}
}

/*
**	int	main(void)
**	{
**		ft_putstr_non_printable("coucou \ntoi !");
**		return (0);
**	}
*/
