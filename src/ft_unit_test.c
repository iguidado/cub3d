/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unit_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:44:16 by iguidado          #+#    #+#             */
/*   Updated: 2020/05/09 18:45:11 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_print_cfg(t_config *cfg)
{
	printf("|%8s|%8s|%8s|%8s|%8s|%8s|%8s|%8s|%8s|\n",
			"mask", "s_width", "s_height", "ceilar_c", "floor_c"
			"no_text", "so_text", "ea_text", "we_text", "spri_text");
	printf("|%8i|%8i|%8i|%8x|%8x|%8s|%8s|%8s|%8s|%8s\n\n",
			cfg->mask, cfg->screen_width, cfg->screen_height,
			cfg->ceilar_color, cfg->floor_color,
			cfg->no_text, cfg->so_text, cfg->ea_text,
			cfg->we_text, cfg->spri_text);
	if (cfg->map.data)
		ft_print_tab(cfg->map.data);
}

void	ft_print_fdata(t_file_data *fdata)
{
	printf("|%8s|%8s|%40s|\n", "fd", "line_nb", "line");
	printf("|%8i|%8i|%40s|\n", fdata->fd, fdata->line_nb, fdata->line);
}

void	ft_print_obj(t_obj_spwn *obj_list)
{
	int i;

	i = 1;
	while (obj_list)
	{
		printf("obj no %i  x = %i, y = %i\n"
				, i, obj_list->pos.x, obj_list->pos.y);
		obj_list = obj_list->next;
		i++;
	}
}
