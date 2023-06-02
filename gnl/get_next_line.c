/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 00:08:35 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/22 16:13:48 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	buff[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	*line = NULL;
	ret = 0;
	while (!ft_dump_line(buff, line))
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if ((ret) < 1)
		{
			if (ret == -1)
			{
				if (*line)
					free(*line);
				line = NULL;
			}
			return (ret);
		}
	}
	return (1);
}
