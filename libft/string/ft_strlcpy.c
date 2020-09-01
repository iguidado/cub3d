/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:10:55 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/20 00:06:55 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t trying_to_cpy;

	if (!src)
		return (0);
	trying_to_cpy = ft_strlen(src);
	if (!dstsize || !dest)
		return (trying_to_cpy);
	while (dstsize > 1 && *src)
	{
		*dest = *src;
		dest++;
		src++;
		dstsize--;
	}
	*dest = '\0';
	return (trying_to_cpy);
}

/*
**	#include <unistd.h>
**	int	main(void)
**	{
**		char hello[20] = "lol\0si tu decon";
**		char ref[20] = "lil\0si tu decon";
**		int		i = 0;
**		while (i < 10)
**		{
**			write(1, "-", 1);
**			write(1, &"0123456789"[strlcpy(ref, "Hello !", i)], 1);
**			write(1, "-", 1);
**			write(1, ref, i);
**			write(1, "|", 1);
**			write(1, (ref + i), 10);
**			write(1, "\n", 1);
**			write(1, "-", 1);
**			write(1, &"0123456789"[ft_strlcpy(hello, "Hello !", i)], 1);
**			write(1, "-", 1);
**			write(1, hello, i);
**			write(1, "|", 1);
**			write(1, (hello + i), 10);
**			write(1, "\n", 1);
**			write(1, "\n", 1);
**			i++;
**		}
**		return (0);
**	}
*/
