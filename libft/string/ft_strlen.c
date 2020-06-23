/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:57:51 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/26 18:08:17 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}
/*
**	size_t	ft_strlen(const char *s)
**	{
**		size_t	size;
**		size_t	x;
**		size_t	*i_str;
**
**		size = 0;
**		i_str = (size_t *)s;
**		while ((x = *i_str++))
**		{
**			if (!(x & 0xff))
**				return (size);
**			if (!(x & 0xff00))
**				return (size + 1);
**			if (!(x & 0xff0000))
**				return (size + 2);
**			if (!(x & 0xff000000))
**				return (size + 3);
**			size += sizeof(size_t);
**		}
**		return (0);
**	}
**
**	void	ft_putnbr(int nbr);
**	int	main(void)
**	{
**		int l;
**
**		l = (int)ft_strlen("Hello World !");
**		ft_putnbr(l);
**		return (0);
**	}
*/
