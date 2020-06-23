/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:24:55 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/20 02:26:13 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int	ft_strchr_set(char c, char const *set)
{
	int i;

	i = 0;
	if (!set)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int	get_last_i(char const *s1, char const *set)
{
	int i;

	i = 0;
	while (s1[i])
		i++;
	i--;
	while (ft_strchr_set(s1[i], set) && i > -1)
		i--;
	return (i + 1);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		last_i;
	char	*strtrimmed;

	if (!s1)
		return (NULL);
	i = 0;
	while (ft_strchr_set(*s1, set))
		s1++;
	last_i = get_last_i(s1, set);
	if (!(strtrimmed = (char *)malloc(sizeof(char) * (last_i + 1))))
		return (NULL);
	while (i < last_i)
	{
		strtrimmed[i] = s1[i];
		i++;
	}
	strtrimmed[last_i] = '\0';
	return ((char *)strtrimmed);
}

/*
**	#include "libft.h"
**	int	main(void)
**	{
**		PUTNBR(get_last_i("            ", " "));
**		PUTSTR(ft_strtrim("            ", " "));
**		return (0);
**	}
*/
