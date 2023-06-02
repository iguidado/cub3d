/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:48:19 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/22 18:29:25 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 **	char		*ft_reverse_row(char *row)
 **	{
 **		int		i;
 **		int		strlen;
 **		char	*rev_str;
 **	
 **		i = 0;
 **		strlen = ft_strlen(row);
 **		rev_str = malloc(sizeof(char) * (strlen + 1));
 **		rev_str[strlen] = 0;
 **		while (row[i])
 **		{
 **			rev_str[strlen - i - 1] = row[i];
 **			i++;
 **		}
 **		return (rev_str);
 **	}
 */

/*
 **	int			ft_set_map(t_file_data *fdata, t_map *map)
 **	{
 **		map->map = ft_split(fdata->line, ' ');
 **
 **	}
 */

/*
 **	Maybe to a manip malloc lib
 **
 **	  char		*ft_add_newline(char **str)
 **	  {
 **		char *new;
 **		int strlen;
 **
 **		strlen = ft_strlen(*str);
 **		if (!(new = (char *)malloc(sizeof(char) * (strlen + 2))))
 **			return (NULL);
 **		new[strlen + 1] = '\0';
 **		new[strlen] = '\n';
 **		while (strlen--)
 **			new[strlen] = (*str)[strlen];
 **		free(*str);
 **		return (new);
 **	  }
 */

/*
 **	Don't enter bad value, it will crash
 */

/*
 **	can replace  ft_isset, to see if it is more performant
 **
 **	char		ft_istile(char c)
 **	{
 **		if ((c >= '0' && c <= '2') || c == ' ')
 **			return (1);
 **		if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
 **			return (2);
 **		return (0);
 **	}
 */

int	ft_free_map(char ***map, int y)
{
	char	**map_cpy;

	map_cpy = *map;
	while (y--)
		free(map_cpy[y]);
	free(*map);
	*map = NULL;
	return (0);
}

int	ft_equalize_row(t_map *map)
{
	int		y;
	int		x;
	char	*new;

	y = -1;
	while (map->data[++y])
	{
		x = 0;
		new = malloc(sizeof(char) * (map->res.x + 1));
		if (!new)
			return (0);
		new[map->res.x] = 0;
		while (map->data[y][x])
		{
			new[map->res.x - 1 - x] = map->data[y][x];
			x++;
		}
		while (map->res.x - x - 1 >= 0)
			new[map->res.x - x++ - 1] = ' ';
		free(map->data[y]);
		map->data[y] = new;
	}
	return (1);
}

void	ft_process_map(t_config *cfg, t_file_data *fdata)
{
	int		x;
	int		y;

	fdata->line = NULL;
	if (!ft_equalize_row(&cfg->map))
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	y = 0;
	while (cfg->map.data[y])
	{
		x = 0;
		while (cfg->map.data[y][x])
		{
			ft_process_tile(cfg, fdata, x, y);
			x++;
		}
		y++;
	}
	cfg->map.res.y = y;
	if (cfg->spwn.pos.x < 0)
		ft_manage_parse_error(ERROR_MAP_PLAYER_SPAWN, cfg, fdata);
	cfg->map.data[cfg->spwn.pos.y][cfg->spwn.pos.x] = '0';
}

static void	ft_get_to_map(t_config *cfg, t_file_data *fdata)
{
	int			ret;

	while (!ft_line_is_map(fdata->line))
	{
		free(fdata->line);
		fdata->line = NULL;
		ret = get_next_line(fdata->fd, &fdata->line);
		if (ret == -1)
			ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
		else if (!ret)
			ft_manage_parse_error(ERROR_FILE_END, cfg, fdata);
		fdata->line_nb++;
	}
}

void	ft_add_map(t_config *cfg, t_file_data *fdata)
{
	ft_get_to_map(cfg, fdata);
	if (!ft_add_row(&cfg->map.data, fdata->line))
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	cfg->map.res.x = ft_strlen(fdata->line);
	while (get_next_line(fdata->fd, &fdata->line))
	{
		if (!ft_add_row(&cfg->map.data, fdata->line))
			ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
		if (ft_strlen(fdata->line) > cfg->map.res.x)
			cfg->map.res.x = ft_strlen(fdata->line);
	}
	if (!ft_add_row(&cfg->map.data, fdata->line))
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	ft_process_map(cfg, fdata);
}
