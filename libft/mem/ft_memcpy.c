/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:41:01 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/18 10:07:39 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	size_t				i;
	unsigned char		*tmp_dest;
	unsigned char		*tmp_src;

	i = 0;
	if ((!dest && !src) && n)
		return (NULL);
	tmp_dest = (unsigned char*)dest;
	dest = (void *)tmp_dest;
	tmp_src = (unsigned char*)src;
	while (i < n)
	{
		*tmp_dest = *tmp_src;
		tmp_dest++;
		tmp_src++;
		n--;
	}
	return (dest);
}

/*
**	void	ft_print_memory(void *ptr, unsigned int n);
**	char	*ft_strdup(char *str);
**	int	main()
**	{
**		void	*lol;
**
**		lol = NULL;
**		ft_print_memory(memcpy(lol, NULL, 10), 16);
**		return (0);
**	}
*/
