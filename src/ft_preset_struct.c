/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preset_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:48:50 by iguidado          #+#    #+#             */
/*   Updated: 2022/09/26 02:27:23 by lescribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_file_data	ft_preset_fdata(int ac, char **av)
{
	t_file_data	fdata;

	if (ac < 2 || ac > 4)
	{
		ft_putendl("Error\nBad nbr of argument");
		exit(EXIT_FAILURE);
	}
	if (!ft_strendby(av[1], ".cub"))
	{
		ft_putendl_fd("file format is incorrect it should end by .cub", 2);
		exit (1);
	}
	fdata.fd = open(av[1], O_RDONLY);
	if ((fdata.fd) < 0)
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

t_config	ft_preset_config(void)
{
	t_config	new;

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
	new.map.data = NULL;
	new.map.res.x = 0;
	new.map.res.y = 0;
	new.obj_list = NULL;
	return (new);
}

t_player	ft_preset_player(t_config *cfg)
{
	t_player	new;

	new.x = ((float)cfg->spwn.pos.x) + 0.5f;
	new.y = ((float)cfg->spwn.pos.y) + 0.5f;
	new.angle = cfg->spwn.angle;
	new.fov = (M_PI / 4.0f);
	new.speed = PLAYER_SPEED;
	new.key_id[INPUT_W] = KEY_W;
	new.key_id[INPUT_A] = KEY_A;
	new.key_id[INPUT_S] = KEY_S;
	new.key_id[INPUT_D] = KEY_D;
	new.key_id[INPUT_LEFT] = KEY_LEFT;
	new.key_id[INPUT_RIGHT] = KEY_RIGHT;
	new.key_id[INPUT_ESC] = KEY_ESC;
	ft_memset(new.input, 0, sizeof(new.input));
	return (new);
}

t_img	ft_preset_img(t_config *cfg)
{
	t_img	new;
	t_dot	res_max;
	int		bpp;
	int		linelen;
	int		endian;

	new.mlx_ptr = mlx_init();
	if (!new.mlx_ptr)
		exit(1);
	mlx_get_screen_size(new.mlx_ptr, &res_max.y, &res_max.x);
	if (res_max.y < cfg->screen_width)
		cfg->screen_width = res_max.y;
	if (res_max.x < cfg->screen_height)
		cfg->screen_height = res_max.x;
	new.win_ptr = mlx_new_window(new.mlx_ptr, cfg->screen_width,
			cfg->screen_height, "cub3d");
	new.img_ptr = mlx_new_image(new.mlx_ptr, cfg->screen_width,
			cfg->screen_height);
	new.img_width = cfg->screen_width;
	new.img_height = cfg->screen_height;
	new.img_data = mlx_get_data_addr(new.img_ptr, &bpp, &linelen, &endian);
	new.no_text = ft_load_text(&new, cfg->no_text);
	new.so_text = ft_load_text(&new, cfg->so_text);
	new.ea_text = ft_load_text(&new, cfg->ea_text);
	new.we_text = ft_load_text(&new, cfg->we_text);
	return (new);
}

t_prm_pkg	ft_pkg_prm(t_config *cfg, t_img *img, t_player *pl, t_pos_lst **obj)
{
	t_prm_pkg	new;

	new.cfg = cfg;
	new.img = img;
	new.one = pl;
	new.obj_lst = *obj;
	return (new);
}
