/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:01:25 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/26 18:03:51 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int sign;
	int nbr;

	sign = 1;
	nbr = 0;
	while (*str == 32 || (*str >= 8 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + ((*str) - '0');
		str++;
	}
	return (nbr * sign);
}

/*
**	#include <stdlib.h>
**	void	ft_putnbr(int nbr);
**	int	main(void)
**	{
**		ft_putnbr(atoi("   -    13        "));
**		return (0);
**	}
*/
