/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 02:52:27 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/21 17:59:02 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

bool	ft_strendby(char *str, char *end)
{
	int	i;
	int	j;

	i = ft_strlen(str);
	j = ft_strlen(end);
	if (i < j)
		return (false);
	if (j == 0)
		return (true);
	j--;
	i--;
	while (j >= 0)
	{
		if (str[i] != end[j])
			return (false);
		j--;
		i--;
	}
	return (true);
}

int	ft_isxpm(char *input)
{
	void	*ptr;
	void	*xpm_ptr;
	int		disc;
	int		ret;

	ret = ERROR_XPM;
	ptr = mlx_init();
	if (!ptr)
		return (ERROR_SYSCALL);
	xpm_ptr = mlx_xpm_file_to_image(ptr, input,
			&disc, &disc);
	if (xpm_ptr)
	{
		ret = 1;
		mlx_destroy_image(ptr, xpm_ptr);
	}
	mlx_destroy_display(ptr);
	free(ptr);
	return (ret);
}
