/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:52:56 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/18 10:38:05 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*src_tmp;
	unsigned char	*dest_tmp;

	if ((!dest && !src) && len)
		return (NULL);
	src_tmp = (unsigned char *)src;
	dest_tmp = (unsigned char *)dest;
	if (dest > src)
	{
		while (len--)
			dest_tmp[len] = src_tmp[len];
	}
	else
	{
		while (len--)
		{
			*dest_tmp = *src_tmp;
			dest_tmp++;
			src_tmp++;
		}
	}
	return (dest);
}

/*
**	void	ft_print_memory(void *addr, unsigned int size);
**	int	main(void)
**	{
**		void *ptr_from;
**		void *ptr_to;
**		char a = 'a';
**
**		ptr_from = &a;
**		ptr_to = (void *)malloc(sizeof(void) * 10);
**		ft_print_memory(ptr_from, 15);
**		ft_memmove(ptr_to, ptr_from, 10);
**		ft_print_memory(ptr_to, 15);
**		return (0);
**	}
*/
