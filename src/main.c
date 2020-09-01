/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:52:36 by iguidado          #+#    #+#             */
/*   Updated: 2020/08/28 01:18:50 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_escape_game(t_prm_pkg *cub)
{
	ft_putendl("escaping game");
	ft_wipe_cfg(cub->cfg);
	ft_wipe_obj(&cub->obj_lst);
	if (cub->one)
		free(cub->one);
	if (cub->img)
	{
		ft_wipe_img(cub->img);
		free(cub->img);
		if (cub->z_buffer)
			free(cub->z_buffer);
	}
	exit(EXIT_SUCCESS);
}

int		ft_prep_escape(t_player *one)
{
	one->input[INPUT_ESC] = true;
	return (0);
}

int		ft_main_loop(void *param)
{
	t_prm_pkg	*cub;
	t_player	one_ghost;

	cub = (t_prm_pkg *)param;
	ft_memcpy(&one_ghost, cub->one, sizeof(*cub->one));
	ft_move_player(&one_ghost);
	if (cub->one->input[INPUT_ESC])
		ft_escape_game(cub);
	if (!ft_is_oob(&cub->cfg->map, one_ghost.x, one_ghost.y))
		ft_memcpy(cub->one, &one_ghost, sizeof(*cub->one));
	ft_render_screen(param);
	return (0);
}

void	ft_launch_game(t_config cfg)
{
	int				errnum;
	t_prm_pkg		pkg;
	t_pos_lst		*obj_lst;

	if ((errnum = ft_init_pkg(&cfg, &pkg)))
		ft_manage_run_error(errnum, &pkg);
	ft_render_screen((void *)&pkg);
	if (!cfg.mask)
	{
		ft_render_screen((void *)&pkg);
		ft_export_bmp(pkg.img);
		ft_escape_game(&pkg);
	}
	mlx_hook(pkg.img->win_ptr, 17, (1L << 17), &ft_prep_escape, pkg.one);
	mlx_hook(pkg.img->win_ptr, 2, (1L << 0), ft_get_input, &pkg);
	mlx_hook(pkg.img->win_ptr, 3, 2, ft_release_input, &pkg);
	mlx_loop_hook(pkg.img->mlx_ptr, ft_main_loop, &pkg);
	mlx_loop(pkg.img->mlx_ptr);
}

int		main(int ac, char **av)
{
	int				errnum;
	t_file_data		fdata;
	t_config		setup_cfg;

	if ((errnum = ft_init_fdata(ac, av, &fdata)) >= 0)
		ft_manage_parse_error(errnum, NULL, &fdata);
	setup_cfg = ft_get_config(&fdata);
	ft_add_map(&setup_cfg, &fdata);
	ft_wipe_file_data(&fdata);
	if (ac > 2)
	{
		if (ft_strequ(av[2], "--save"))
			setup_cfg.mask = 0;
	}
	ft_launch_game(setup_cfg);
	return (0);
}
