/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 20:49:35 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/19 14:22:21 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i])
			i++;
		write(fd, s, i);
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
**		ft_putstr_fd("world", fd);
**		return (0);
**	}
*/
