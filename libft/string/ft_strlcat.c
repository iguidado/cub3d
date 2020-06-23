/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:58:08 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/26 18:05:56 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	while (dest[i] && i < size)
		i++;
	if (i == size)
		return (j + size);
	j = 0;
	while (j < (size - i - 1) && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}

/*
**	#include <unistd.h>
**	#include "libft.h"
**	int	main(void)
**	{
**		char dest[100] = "xxxxx";
**		char ref[100] = "xxxxx";
**		int i;
**
**		i = 0;
**		while (i < 50)
**		{
**			strcpy(ref, "");
**			write(1, "-", 1);
**			write(1, &"0123456789abcdefghijkl"[strlcat(ref, "H", i)], 1);
**			write(1, "-", 1);
**			write(1, ref, ft_strlen(ref));
**			write(1, "\n", 1);
**			strcpy(dest, "");
**			write(1, "-", 1);
**			write(1, &"0123456789abcdefghijkl"[ft_strlcat(dest, "H", i)], 1);
**			write(1, "-", 1);
**			write(1, dest, ft_strlen(dest));;
**			write(1, "\n", 1);
**			write(1, "\n", 1);
**			i++;
**		}
**		return (0);
**	}
*/
