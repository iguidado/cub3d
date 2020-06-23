/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:19:33 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/18 11:08:42 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	i = 0;
	if (!(s && f))
		return (NULL);
	while (s[i])
		i++;
	if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	new[i] = 0;
	while (i-- > 0)
		new[i] = (*f)(i, s[i]);
	return (new);
}

/*
**	char up(unsigned int quisertarien, char voila)
**	{
**		(void)quisertarien;
**		return (voila - ('a' - 'A'));
**	}
**
**	#include <unistd.h>
**
**	int	main(void)
**	{
**		char lol[] = "lolilolil";
**		char *lel;
**
**		lel = ft_strmapi(lol, up);
**		write(1, lel, 10);
**		return (0);
**	}
*/
