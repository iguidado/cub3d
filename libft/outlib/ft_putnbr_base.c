/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 22:41:26 by iguidado          #+#    #+#             */
/*   Updated: 2020/02/07 23:01:03 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	ft_check_base(char *base)
{
	int i;
	int j;

	i = 0;
	if (base[i] == '-' || base[i] == '+')
		return (0);
	while (base[i + 1])
	{
		j = i;
		while (base[++j])
		{
			if (base[i] == base[j])
				return (0);
			if (base[j] == '-' || base[j] == '+')
				return (0);
		}
		i++;
	}
	if (j < 2)
		return (0);
	return (j);
}

static void	ft_recurse_putbase(int nbr, char *base, int base_len)
{
	if (nbr < -base_len || nbr > base_len)
		ft_recurse_putbase(nbr / base_len, base, base_len);
	nbr = nbr % base_len;
	nbr = (nbr < 0 ? -nbr : nbr);
	write(1, &base[nbr], 1);
}

void		ft_putnbr_base(int nbr, char *base)
{
	int base_len;

	if (!(base_len = ft_check_base(base)))
	{
		write(1, "Error, bad base", 15);
		return ;
	}
	if (nbr < 0)
		write(1, "-", 1);
	ft_recurse_putbase(nbr, base, base_len);
}
