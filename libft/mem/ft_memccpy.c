/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:51:24 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/05 18:36:40 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest_tmp;
	unsigned char	*src_tmp;

	dest_tmp = (unsigned char *)dest;
	src_tmp = (unsigned char *)src;
	while (n)
	{
		if (*src_tmp == (unsigned char)c)
		{
			*dest_tmp = (unsigned char)c;
			return ((void *)++dest_tmp);
		}
		*dest_tmp = *src_tmp;
		dest_tmp++;
		src_tmp++;
		n--;
	}
	return (NULL);
}

/*
**	void	ft_strcpy(char *, char *);
**	void	ft_print_memory(voiiiiid *, int);
**	int	main(void)
**	{
**		char hello[20];
**		char dest[20];
**
**		ft_strcpy(hello, "Hello World !");
**		ft_memccpy(dest, hello, 'W', 10);
**		ft_print_memory(dest, 10);
**		return (0);
**	}
*/
