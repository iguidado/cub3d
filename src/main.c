/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:52:36 by iguidado          #+#    #+#             */
/*   Updated: 2020/12/31 15:39:37 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_is_oob(t_map *map, float x, float y)
{
	if (x < 0.0f || y < 0.0f)
		return (1);
	if (((int)x) >= map->res.x || ((int)y) >= map->res.y)
		return (1);
	return (0);
}

int			ft_get_input(int keycode, void *param)
{
	int			i;
	t_prm_pkg	*pkg;

	pkg = (t_prm_pkg *)param;
	i = 0;
	while (i < NB_INPUT)
	{
		if (pkg->one->key_id[i] == keycode)
			pkg->one->input[i] = true;
		i++;
	}
	return (0);
}

int			ft_release_input(int keycode, void *param)
{
	int			i;
	t_prm_pkg	*pkg;

	pkg = (t_prm_pkg *)param;
	i = 0;
	while (i < NB_INPUT)
	{
		if (pkg->one->key_id[i] == keycode)
			pkg->one->input[i] = false;
		i++;
	}
	return (0);
}

void		ft_move_player(t_player *one)
{
	if (one->input[INPUT_LEFT])
		one->angle += 0.1f;
	if (one->input[INPUT_RIGHT])
		one->angle -= 0.1f;
	if (one->input[INPUT_W])
	{
		one->x += sin(one->angle) * one->speed;
		one->y += cos(one->angle) * one->speed;
	}
	if (one->input[INPUT_A])
	{
		one->x -= cos(one->angle) * one->speed;
		one->y += sin(one->angle) * one->speed;
	}
	if (one->input[INPUT_S])
	{
		one->x -= sin(one->angle) * one->speed;
		one->y -= cos(one->angle) * one->speed;
	}
	if (one->input[INPUT_D])
	{
		one->x += cos(one->angle) * one->speed;
		one->y -= sin(one->angle) * one->speed;
	}
}

void		ft_escape_game(t_prm_pkg *cub)
{
	ft_putendl("escaping game");
	free(cub->z_buffer);
	ft_wipe_cfg(cub->cfg);
	ft_wipe_obj(&cub->obj_lst);
	ft_wipe_img(cub->img);
	exit(EXIT_SUCCESS);
}

int			ft_prep_escape(t_prm_pkg *pkg)
{
	pkg->one->input[INPUT_ESC] = true;
	return (0);
}

int			ft_main_loop(void *param)
{
	t_prm_pkg	*cub;
	t_player	one_ghost;

	cub = (t_prm_pkg *)param;
	ft_memcpy(&one_ghost, cub->one, sizeof(*cub->one));
	ft_move_player(&one_ghost);
	if (cub->one->input[INPUT_ESC])
		ft_escape_game(cub);
	if (!ft_is_oob(&cub->cfg->map, one_ghost.x, one_ghost.y))
	{
		ft_memcpy(cub->one, &one_ghost, sizeof(*cub->one));
	}
	ft_render_screen(param);
	return (0);
}

void		ft_launch_game(t_config cfg)
{
	t_player		one;
	t_img			img;
	t_prm_pkg		pkg;
	t_pos_lst		*obj_lst;

	one = ft_preset_player(&cfg);
	img = ft_preset_img(&cfg);
	obj_lst = ft_load_obj(cfg.obj_list);
	pkg = ft_pkg_prm(&cfg, &img, &one, &obj_lst);
	pkg.z_buffer = malloc(sizeof(float) * img.img_width + 1);
	ft_render_screen((void *)&pkg);
	printf("%i, %i\n", cfg.map.res.x, cfg.map.res.y);
	if (!cfg.mask)
	{
		ft_render_screen((void *)&pkg);
		ft_export_bmp(&img);
		ft_escape_game(&pkg);
	}
	mlx_hook(img.win_ptr, 17, (1L << 17), &ft_prep_escape, &pkg);
	mlx_hook(img.win_ptr, 2, (1L << 0), ft_get_input, &pkg);
	mlx_hook(img.win_ptr, 3, 2, ft_release_input, &pkg);
	mlx_loop_hook(img.mlx_ptr, ft_main_loop, &pkg);
	mlx_loop(img.mlx_ptr);
}

int			main(int ac, char **av)
{
	t_file_data		fdata;
	t_config		setup_cfg;

	fdata = ft_preset_fdata(ac, av);
	setup_cfg = ft_get_config(&fdata);
	ft_add_map(&setup_cfg, &fdata);
	ft_wipe_file_data(&fdata);
	if (ac > 2)
		if (ft_strequ(av[2], "--save"))
			setup_cfg.mask = 0;
	ft_print_tab(setup_cfg.map.data);
	ft_launch_game(setup_cfg);
	ft_print_fdata(&fdata);
	ft_print_cfg(&setup_cfg);
	ft_wipe_cfg(&setup_cfg);
	return (0);
}
