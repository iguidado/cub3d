/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:45:23 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/18 10:33:00 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
**	#include <fcntl.h>
**	#include <stdio.h>
**	int	main(void)
**	{
**		int fd;
**
**		fd = creat("hello", 0666);
**		ft_putchar_fd('a', fd);
**		return (0);
**	}
*/
