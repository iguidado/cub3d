/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:59:06 by iguidado          #+#    #+#             */
/*   Updated: 2020/06/23 17:59:26 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_tab(char ***tab)
{
	char	**tab_cpy;
	int		i;

	tab_cpy = *tab;
	i = 0;
	while (tab_cpy[i])
	{
		free(tab_cpy[i]);
		i++;
	}
	free(tab_cpy);
	*tab = NULL;
}
