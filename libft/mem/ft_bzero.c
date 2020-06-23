/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:37:29 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/26 18:04:06 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char *s_cpy;

	s_cpy = (unsigned char *)s;
	while (n)
	{
		*s_cpy = 0;
		s_cpy++;
		n--;
	}
}

/*
**	void	ft_print_memory(void *, int);
**	int	main(void)
**	{
**		char lol[20] = "lollollollollollol";
**
**		ft_print_memory(lol, 25);
**		ft_bzero(lol, 3);
**		ft_print_memory(lol, 25);
**		return (0);
**	}
*/
