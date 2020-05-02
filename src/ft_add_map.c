#include "cub3d.h"

int			ft_check_map_empty_line(t_file_data *fdata)
{
	int player_count;
	int y;
	int x;

	player_count = 0;
	while (*(fdata->line + 1))
	{
		if (*fdata->line == '\n' && *(fdata->line + 1) == '\n')
			return (0);
		fdata->line++;
	}
	return (1);
}

/*
 **	int			ft_set_map(t_file_data *fdata, t_map *map)
 **	{
 **		map->map = ft_split(fdata->line, ' ');
 **	
 **	}
 */
char		ft_istile(char c)
{

	if ((c >= '0' && c <= '2') || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (2);
	return (0);
}


char		*ft_add_newline(char **str)
{
	char *new;
	int strlen;

	strlen = ft_strlen(*str);
	if (!(new = (char *)malloc(sizeof(char) * (strlen + 2))))
		return (NULL);
	new[strlen + 1] = '\0';
	new[strlen] = '\n';
	while (strlen--)
		new[strlen] = (*str)[strlen];
	free(*str);
	return (new);
}

int			ft_is_border_map(char **map, int x, int y)
{
	if ((x == 0 || !map[y + 1]) 
			|| ((y == 0) || !map[y][x + 1]))
		return (1);
	return (0);
}

int			ft_cross_check_bound(t_config *cfg, t_file_data *fdata, int x, int y)
{
	int i;

	i = 0;
	while (cfg->map[y - 1][i] && i < x)
		i++;
	if (!cfg->map[y - 1][x] || cfg->map[y - 1][x] == ' ')
		return (1);
	i = 0;
	while (cfg->map[y + 1][i] && i < x)
		i++;
	if (!cfg->map[y + 1][i] || cfg->map[y + 1][i] == ' ')
		return (1);
	if (cfg->map[y][x + 1] == ' ' || cfg->map[y][x - 1] == ' ')
		return (1);
	return (0);
}

void		ft_check_tile_type(t_config *cfg, t_file_data *fdata, int x, int y)
{
	if (ft_isset(INTERIOR, cfg->map[y][x]))
	{
		if (ft_is_border_map(cfg->map, x, y))
			ft_manage_parse_error(ERROR_MAP_OPEN_BOUNDARIES, cfg, fdata);
		if (ft_cross_check_bound(cfg, fdata, x, y))
			ft_manage_parse_error(ERROR_MAP_OPEN_BOUNDARIES, cfg, fdata);
	}
}

void		ft_get_spawn(t_config *cfg, t_file_data *fdata, int x, int y)
{
	if (cfg->spwn.pos.x >= 0)
		ft_manage_parse_error(ERROR_MAP_PLAYER_SPAWN, cfg, fdata);
	else
	{
		cfg->spwn.pos.y = y;
		cfg->spwn.pos.x = x;
		if (cfg->map[y][x] == 'N')
			cfg->spwn.angle = M_PI;
		if (cfg->map[y][x] == 'E')
			cfg->spwn.angle = M_PI / 2.0f;
		if (cfg->map[y][x] == 'S')
			cfg->spwn.angle= 0.0f;
		if (cfg->map[y][x] == 'W')
			cfg->spwn.angle = M_PI * (3.0f / 2.0f);
	}
}

void		ft_process_map(t_config *cfg, t_file_data *fdata)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (cfg->map[y])
	{
		x = 0;
		while ((tile = cfg->map[y][x]))
		{
			if (!ft_isset(TILES, tile))
				ft_manage_parse_error(ERROR_MAP_BAD_TILE, cfg, fdata);
			ft_check_tile_type(cfg, fdata, x, y);
			if (ft_isset(SPAWN, tile))
				ft_get_spawn(cfg, fdata, x, y);
			x++;
		}
		y++;
	}
	if (cfg->spwn.pos.x < 0)
		ft_manage_parse_error(ERROR_MAP_PLAYER_SPAWN, cfg, fdata);
	cfg->map[cfg->spwn.pos.y][cfg->spwn.pos.x] = '0';
}

int			ft_add_row(char ***ptr_map, char *row)
{
		int i;
		char **new;

		if (!row)
			return (0);
		i = 0;
		if (*ptr_map)
		{
		while ((*ptr_map)[i])
			i++;
		}
		if (!(new = (char **)malloc(sizeof(char *) * (i + 2))))
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

void		ft_add_map(t_config *cfg, t_file_data *fdata)
{
	int			ret;
	int			map_rows;
	char		*current_line;
	char		*next_line;

	while (!ft_line_is_map(fdata->line))
	{
		free(fdata->line);
		if ((ret = get_next_line(fdata->fd, &fdata->line)) == -1)
			ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
		else if (!ret)
			ft_manage_parse_error(ERROR_FILE_END, cfg, fdata);
		fdata->line_nb++;
	}
	ft_add_row(&cfg->map, fdata->line);
	while (get_next_line(fdata->fd, &fdata->line))
		ft_add_row(&cfg->map, fdata->line);
	ft_add_row(&cfg->map, fdata->line);
	ft_process_map(cfg, fdata);
}
