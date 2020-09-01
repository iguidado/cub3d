/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:20:27 by iguidado          #+#    #+#             */
/*   Updated: 2019/11/26 18:34:00 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	str_l;
	char	*sub;
	size_t	sub_len;
	int		i;

	if (!str)
		return (NULL);
	str_l = ft_strlen(str);
	sub_len = (((size_t)start + len) >= str_l ? str_l - (size_t)start : len);
	if (start >= str_l)
		sub_len = 0;
	if (!(sub = (char *)malloc(sub_len + 1)))
		return (NULL);
	i = 0;
	if (start < str_l)
	{
		while (len && (sub[i] = str[start]))
		{
			i++;
			start++;
			len--;
		}
	}
	sub[i] = '\0';
	return (sub);
}
/*
**	void	*ft_print_memory(void *, int);
**	int	main(void)
**	{
**		char *sub;
**
**		if(!(sub = ft_substr("0123456789", 5, 40)))
**		{
**			PUTENDL("Bad Allocation");
**		}
**		else
**			PUTENDL(sub);
**		ft_print_memory(sub, 20);
**		free(sub);
**		return (0);
**	}
*/
