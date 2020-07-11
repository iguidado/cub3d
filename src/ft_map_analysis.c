/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:39:36 by iguidado          #+#    #+#             */
/*   Updated: 2020/07/04 15:46:09 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_is_border_map(char **map, int x, int y)
{
	if (x == 0 || y == 0 || !map[y + 1])
		return (1);
	if (!map[y][x + 1] || map[y][x + 1] == ' ')
		return (1);
	if (map[y][x - 1] == ' ')
		return (1);
	return (0);
}

int		ft_cross_check_bound(t_config *cfg, int x, int y)
{
	int i;

	i = 0;
	while (cfg->map.data[y - 1][i] && i < x + 2)
	{
		if (i > x - 2 && i < x + 2)
		{
			if (cfg->map.data[y - 1][i] == ' ')
				return (1);
		}
		i++;
	}
	if (i < x + 2)
		return (1);
	i = 0;
	while (cfg->map.data[y + 1][i] && i < x + 2)
	{
		if (i > x - 2 && i < x + 2)
		{
			if (cfg->map.data[y - 1][i] == ' ')
				return (1);
		}
		i++;
	}
	if (i < x + 2)
		return (1);
	return (0);
}

void	ft_check_tile_type(t_config *cfg, t_file_data *fdata, int x, int y)
{
	if (ft_isset(INTERIOR, cfg->map.data[y][x]))
	{
		if (ft_is_border_map(cfg->map.data, x, y))
			ft_manage_parse_error(ERROR_MAP_OPEN_BOUNDARIES, cfg, fdata);
		if (ft_cross_check_bound(cfg, x, y))
			ft_manage_parse_error(ERROR_MAP_OPEN_BOUNDARIES, cfg, fdata);
	}
}
