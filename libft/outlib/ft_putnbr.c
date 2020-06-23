/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 22:55:41 by iguidado          #+#    #+#             */
/*   Updated: 2020/02/07 23:02:07 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nbr)
{
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	write(1, &"0123456789"[nbr % 10], 1);
}

/*
**	#include <limits.h>
**	int	main(void)
**	{
**		ft_putnbr(INT_MIN);
**		write(1, "\n", 1);
**		ft_putnbr(0);
**		write(1, "\n", 1);
**		ft_putnbr(INT_MAX);
**		write(1, "\n", 1);
**		return (0);
**	}
*/
