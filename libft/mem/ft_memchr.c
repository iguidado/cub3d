/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:53:51 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/26 18:04:44 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *s_trlt;

	s_trlt = (unsigned char *)s;
	while (n)
	{
		if (*s_trlt == (unsigned char)c)
			return ((void *)s_trlt);
		s_trlt++;
		n--;
	}
	return (NULL);
}

/*
**	void	ft_print_memory(void *, int);
**	int	main(void)
**	{
**		char hello[20] = "Hello World !";
**
**		ft_print_memory(ft_memchr(hello, 'W', 7), 10);
**		return (0);
**	}
*/
