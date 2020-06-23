/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismsk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 10:00:10 by iguidado          #+#    #+#             */
/*   Updated: 2020/04/14 21:48:02 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_ismsk(char *ref, char *tokens)
{
	char msk;

	msk = 0;
	if (!tokens || !ref)
		return (0);
	while (*tokens)
	{
		msk |= ft_isbit(ref, *tokens);
		tokens++;
	}
	return (msk);
}
