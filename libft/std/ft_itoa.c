/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:53:53 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/22 16:12:33 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_nbrlen_itoa(int nbr)
{
	int	length;

	length = 1 + (nbr < 0);
	while (nbr < -9 || nbr > 9)
	{
		nbr = nbr / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*nbr_array;
	int		i;

	i = ft_nbrlen_itoa(n);
	nbr_array = (char *)malloc(sizeof(char) * (i + 1));
	if (!(nbr_array))
		return (NULL);
	nbr_array[0] = '0';
	if (n < 0)
		nbr_array[0] = '-';
	nbr_array[i] = '\0';
	while (--i)
	{
		if (n < 0)
			nbr_array[i] = (-1 * (n % 10)) + '0';
		else
			nbr_array[i] = (n % 10) + '0';
		n = n / 10;
	}
	if (!(nbr_array[0] == '-'))
		nbr_array[0] = n + '0';
	return (nbr_array);
}

/*
**	void	ft_putnbr(int nbr);
**	void	ft_putendl(char *str);
**	int	main(void)
**	{
**		ft_putnbr(ft_nbrlen_itoa(-1));
**
**		int i = -21;
**		while (i < -20)
**		{
**			ft_putendl(ft_itoa(-2147483648));
**			i++;
**		}
**		return (0);
**	}
*/
