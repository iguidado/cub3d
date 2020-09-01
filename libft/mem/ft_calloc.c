/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:03:39 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/26 18:02:41 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*newstr;
	size_t	i;

	if (!count || !size)
		return (newstr = (char *)malloc(1));
	if (!(newstr = (char *)malloc(count * size)))
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		newstr[i] = 0;
		i++;
	}
	return ((void *)newstr);
}

/*
**	char	*ft_strcpy(char *dest, char *src);
**	void	ft_putendl(char *str);
**	void	ft_print_memory(void *, int);
**	int	main(void)
**	{
**		char *lol;
**
**		lol = (char *)ft_calloc(32, sizeof(char));
**		ft_print_memory(lol, 200);
**		ft_putendl(lol);
**		ft_strcpy(lol, "Hello World !, i'm not supposed to work but let try");
**		return (0);
**	}
*/
