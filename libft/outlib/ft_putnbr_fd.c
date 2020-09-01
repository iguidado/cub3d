/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:08:39 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/19 14:21:24 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			write(fd, "2147483648", 10);
			return ;
		}
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	write(fd, &"0123456789"[n % 10], 1);
}

/*
**	#include <fcntl.h>
**	#include <stdio.h>
**	int	main(void)
**	{
**		int fd;
**
**		fd = creat("hello", 0666);
**		ft_putnbr_fd(-2147483648, fd);
**		return (0);
**	}
*/
