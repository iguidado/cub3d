/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:29:01 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/26 18:05:03 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *new;

	new = b;
	while (len > 1)
	{
		new[len - 1] = (unsigned char)c;
		len--;
	}
	if (len)
		new[0] = (unsigned char)c;
	return (b);
}

/*
**	void	*ft_print_memory(void *addr, int size);
**	int	main(void)
**	{
**		int c;
**		size_t size;
**		char lol;
**		void *ptr;
**
**		ptr = &lol;
**		size = 5;
**		c = 'A';
**		ft_memset(ptr, c, size);
**		ft_print_memory(ptr, 6);
**		return (0);
**	}
*/
