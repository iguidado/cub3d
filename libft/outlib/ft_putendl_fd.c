/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:49:44 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/22 16:07:16 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		write(fd, s, i);
		write(fd, "\n", 1);
	}
	return (i);
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
