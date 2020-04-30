#include "cub3d.h"
#include <stdio.h>

void	ft_print_cfg(t_config *cfg)
{
	printf("|%8s|%8s|%8s|%8s|%8s|%8s|%8s|%8s|%8s|\n", 
			"mask", "s_width", "s_height", "ceilar_c", "floor_c"
			"no_text", "so_text", "ea_text", "we_text", "spri_text");

	printf("|%8i|%8i|%8i|%8i|%8i|%8s|%8s|%8s|%8s|%8s\n\n", 
			cfg->mask, cfg->screen_width, cfg->screen_height, 
			cfg->ceilar_color, cfg->floor_color,
			cfg->no_text, cfg->so_text, cfg->ea_text, 
			cfg->we_text, cfg->spri_text);
	if (cfg->map)
		ft_print_tab(cfg->map);
}

void	ft_print_fdata(t_file_data *fdata)
{
	printf("|%8s|%8s|%40s|\n", "fd", "line_nb", "line");
	printf("|%8i|%8i|%40s|\n", fdata->fd, fdata->line_nb, fdata->line);
}
