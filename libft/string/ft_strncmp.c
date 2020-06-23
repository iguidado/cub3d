/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:14:25 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/25 21:19:03 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 == *s2 && *s1 && --n)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - *s2);
}

/*
**	#include <string.h>
**	void	ft_putchar(char c);
**	void	ft_putnbr(int nbr);
**	int	main(int ac, char **av)
**	{
**		if (ac == 4)
**		{
**			ft_putnbr(strncmp(av[1], av[2], atoi(av[3])));
**			ft_putchar('\n');
**			ft_putnbr(ft_strncmp(av[1], av[2], atoi(av[3])));
**		}
**		return (0);
**	}
*/
