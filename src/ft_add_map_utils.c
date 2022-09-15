/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lescribe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:48:43 by lescribe          #+#    #+#             */
/*   Updated: 2022/09/15 16:35:34 by lescribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_process_tile(t_config *cfg, t_file_data *fdata, int x, int y)
{
	if (!ft_isset(TILES, cfg->map.data[y][x]))
		ft_manage_parse_error(ERROR_MAP_BAD_TILE, cfg, fdata);
	ft_check_tile_type(cfg, fdata, x, y);
	if (ft_isset(SPAWN, cfg->map.data[y][x]))
		ft_get_spawn(cfg, fdata, x, y);
	if (cfg->map.data[y][x] == '2')
		ft_add_obj(cfg, fdata, x, y);
}

int	ft_add_row(char ***ptr_map, char *row)
{
	int		i;
	char	**new;

	if (!row)
		return (0);
	i = 0;
	if (*ptr_map)
	{
		while ((*ptr_map)[i])
			i++;
	}
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!(new))
		return (0);
	new[i + 1] = 0;
	new[i] = row;
	while (i--)
		new[i] = (*ptr_map)[i];
	if (*ptr_map)
		free(*ptr_map);
	*ptr_map = new;
	return (1);
}

void	ft_get_spawn(t_config *cfg, t_file_data *fdata, int x, int y)
{
	if (cfg->spwn.pos.x >= 0)
		ft_manage_parse_error(ERROR_MAP_PLAYER_SPAWN, cfg, fdata);
	else
	{
		cfg->spwn.pos.y = y;
		cfg->spwn.pos.x = x;
		if (cfg->map.data[y][x] == 'N')
			cfg->spwn.angle = M_PI;
		if (cfg->map.data[y][x] == 'E')
			cfg->spwn.angle = M_PI / 2.0f;
		if (cfg->map.data[y][x] == 'S')
			cfg->spwn.angle = 0.0f;
		if (cfg->map.data[y][x] == 'W')
			cfg->spwn.angle = M_PI * (3.0f / 2.0f);
	}
}
