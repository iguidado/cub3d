/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preset_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:48:50 by iguidado          #+#    #+#             */
/*   Updated: 2020/04/29 01:52:20 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_config		ft_preset_config(void)
{
	t_config new;

	new.mask = 0;
	new.screen_width = -1;
	new.screen_height = -1;
	new.ceilar_color = -1;
	new.floor_color = -1;
	new.no_text = NULL;
	new.so_text = NULL;
	new.ea_text = NULL;
	new.we_text = NULL;
	new.spri_text = NULL;
	new.spwn.pos.x = -1;
	new.spwn.pos.y = -1;
	new.spwn.angle = -1;
	new.map = NULL;
	return (new);
}

t_file_data		ft_preset_fdata(int ac, char **av)
{
	t_file_data fdata;

	if (ac < 2 || ac > 4)
	{
		ft_putendl("Error\nBad nbr of argument");
		exit(EXIT_FAILURE);
	}
	if ((fdata.fd = open(av[1], O_RDONLY)) < 0)
	{
		perror(av[1]);
		exit(errno);
	}
	fdata.name = av[1];
	fdata.line_nb = 0;
	fdata.line = NULL;
	fdata.paramlist = NULL;
	return (fdata);
}

t_player		ft_preset_player(t_config *cfg)
{
	t_player new;

	new.x = ((float)cfg->spwn.pos.x) + 0.5f;
	new.y = ((float)cfg->spwn.pos.y) + 0.5f;
	new.angle = cfg->spwn.angle;
	new.fov = FOV;
	return (new);
}
