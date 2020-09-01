/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 00:16:19 by iguidado          #+#    #+#             */
/*   Updated: 2020/08/28 00:20:42 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_get_spawn(t_config *cfg, t_file_data *fdata, int x, int y)
{
	if (cfg->spwn.pos.x >= 0)
		ft_manage_parse_error(ERROR_PLAYER_MAP, cfg, fdata);
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

void		ft_add_obj(t_config *cfg, t_file_data *fdata, int x, int y)
{
	t_obj_spwn *new;

	if (!(new = (t_obj_spwn *)malloc(sizeof(t_obj_spwn))))
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	new->pos.x = x;
	new->pos.y = y;
	cfg->map.data[y][x] = '0';
	new->next = cfg->obj_list;
	cfg->obj_list = new;
}

int			ft_equalize_row(t_map *map)
{
	int		y;
	int		x;
	char	*new;

	y = -1;
	while (map->data[++y])
	{
		if (!(new = malloc(sizeof(char) * (map->res.x + 1))))
			return (0);
		new[map->res.x] = 0;
		x = -1;
		while (map->data[y][++x])
			new[map->res.x - 1 - x] = map->data[y][x];
		while (map->res.x - x - 1 >= 0)
		{
			new[map->res.x - x - 1] = ' ';
			x++;
		}
		if (map->data[y])
			free(map->data[y]);
		map->data[y] = new;
	}
	return (1);
}

void		ft_check_map_data(t_config *cfg, t_file_data *fdata)
{
	if (cfg->spwn.pos.x < 0)
		ft_manage_parse_error(ERROR_PLAYER_MAP, cfg, fdata);
	if (!cfg->obj_list)
		ft_manage_parse_error(ERROR_SPRI_MAP, cfg, fdata);
	cfg->map.data[cfg->spwn.pos.y][cfg->spwn.pos.x] = '0';
}

void		ft_process_map(t_config *cfg, t_file_data *fdata)
{
	int		x;
	int		y;
	char	tile;

	y = -1;
	while (cfg->map.data[++y])
	{
		fdata->line_nb++;
		x = -1;
		while ((tile = cfg->map.data[y][++x]))
		{
			if (!ft_isset(TILES, tile))
				ft_manage_parse_error(ERROR_UNKWN_MAP, cfg, fdata);
			ft_check_tile_type(cfg, fdata, x, y);
			if (ft_isset(SPAWN, tile))
				ft_get_spawn(cfg, fdata, x, y);
			if (tile == '2')
				ft_add_obj(cfg, fdata, x, y);
		}
	}
	cfg->map.res.y = y;
}
