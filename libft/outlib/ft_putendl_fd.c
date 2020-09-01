/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:49:44 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/19 14:21:51 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i])
			i++;
		write(fd, s, i);
		write(fd, "\n", 1);
	}
}

/*
**	#include <fcntl.h>
**	#include <stdio.h>
**	int	main(void)
**	{
**		int fd;
**
**		fd = creat("hello", 0666);
**		ft_putendl_fd("world", fd);
**		return (0);
**	}
*/
