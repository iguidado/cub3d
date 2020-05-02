/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:25:50 by iguidado          #+#    #+#             */
/*   Updated: 2020/01/18 00:19:59 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

int	ft_manage_buf(char *buf)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n' && i < BUFFER_SIZE)
	{
		buf[i] = '\0';
		i++;
	}
	if (buf[i] == '\0')
		return (0);
	while (++i < BUFFER_SIZE)
	{
		buf[j] = buf[i];
		j++;
	}
	while (j < BUFFER_SIZE)
	{
		buf[j] = 0;
		j++;
	}
	return (1);
}

int	ft_dump_line(char *buf, char **line)
{
	int		i;
	int		j;
	char	*new;

	if (!*buf)
		return (0);
	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n' && i < BUFFER_SIZE)
		i++;
	while ((*line) && (*line)[j])
		j++;
	new = (char *)malloc(sizeof(char) * (i + j + 1));
	new[i + j] = 0;
	while (i-- > 0)
		new[j + i] = buf[i];
	while (j-- > 0)
		new[j] = (*line)[j];
	if (*line)
		free(*line);
	*line = new;
	return (ft_manage_buf(buf));
}
/*
**	#include "libft.h"
**	int		main(void)
**	{
**		char buff_test[BUFFER_SIZE] = "0123456789";
**		char *line = NULL;
**		char **line_ptr = &line;
**
**		ft_print_memory((void *)buff_test, BUFFER_SIZE + 1);
**		ft_putnbr(ft_dump_buf(buff_test, line_ptr));
**		P('\n');
**		ft_print_memory((void *)buff_test, BUFFER_SIZE + 1);
**		ft_putendl(line);
**		return (0);
**	}
*/
