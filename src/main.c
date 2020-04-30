/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:52:36 by iguidado          #+#    #+#             */
/*   Updated: 2020/05/01 00:19:10 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill_screen(t_config *cfg, t_img *img, t_ray_x *ray)
{
	int i;
	int	*screen;
	int	ceiling;
	int floor;

	i = ray->x;
	screen = (int *)img->img_data;
	ceiling = (cfg->screen_height / 2.0f) - cfg->screen_height / ((float)ray->len);
	floor = cfg->screen_height - ceiling;
	while (i < (ceiling * cfg->screen_width))
	{
		screen[i] = cfg->ceilar_color;
		i += cfg->screen_width;
	}
	while (i < (floor * cfg->screen_width))
	{
		screen[i] = 0x0000FF00;
		i += cfg->screen_width;
	}
	while (i < (cfg->screen_height * cfg->screen_width))
	{
		screen[i] = cfg->floor_color;
		i += cfg->screen_width;
	}
}

int		ft_raycast(void *param)
{
	t_ray_x		ray;
	t_prm_pkg	*cub;
	int			wall_hitted;

	ray.x = 0;
	cub = (t_prm_pkg *)param;
	while (ray.x < cub->cfg->screen_width)
	{
		ray.angle = (cub->one->angle - cub->one->fov / 2.0f) + ((float)ray.x / (float)cub->cfg->screen_width) * cub->one->fov;
		ray.eye_x = sin(ray.angle);
		ray.eye_y = cos(ray.angle);
		wall_hitted = 0;
		ray.len = 0.0f;
		while (!wall_hitted)
		{
			ray.len += 0.01f;
			ray.test_x = (int)(cub->one->x + ray.eye_x * ray.len);
			ray.test_y = (int)(cub->one->y + ray.eye_y * ray.len);
			if (cub->cfg->map[ray.test_y][ray.test_x] == '1')
				wall_hitted++;
		}
		ft_fill_screen(cub->cfg, cub->img, &ray);
		ray.x++;
	}
	return (0);
}

int		ft_move_player(int keycode, void *param)
{
	t_prm_pkg *cub;
	
	cub = (t_prm_pkg *)param;
/*
**	if (keycode == KEY_W)
**	{
**		cub->one->x = cub->one->x + cos(cub->one->angle) * 2.0f;
**		cub->one->y = cub->one->y + sin(cub->one->angle) * 2.0f;
**	}
**	if (keycode == KEY_A)
**	{
**		cub->one->x = cub->one->x + cos(cub->one->angle * M_PI * 1.0f);
**		cub->one->y = cub->one->y + sin(cub->one->angle * M_PI * 1.0f);
**	}
**	if (keycode == KEY_S)
**	{
**		cub->one->x = cub->one->x + cos(cub->one->angle * M_PI);
**		cub->one->y = cub->one->y + sin(cub->one->angle * M_PI);
**	//cub->one->x = cub->one->x - cos(cub->one->angle);
**	//cub->one->y = cub->one->y - sin(cub->one->angle);
**	}
**	if (keycode == KEY_D)
**	{
**		cub->one->x = cub->one->x + cos(cub->one->angle * M_PI * 1.5f);
**		cub->one->y = cub->one->y + sin(cub->one->angle * M_PI * 1.5f);
**	}
*/
	if (keycode == KEY_LEFT)
	{
	ft_putnbr(keycode);
	ft_putchar('\n');
		cub->one->angle -= 0.3f;
	}
	if (keycode == KEY_RIGHT)
	{
	ft_putnbr(keycode);
	ft_putchar('\n');
		cub->one->angle += 0.3f;
	}
	ft_raycast(param);
	mlx_put_image_to_window(cub->img->mlx_ptr, cub->img->win_ptr, cub->img->img_ptr, 0, 0);
	return (0);
}

void	ft_launch_game(t_config cfg)
{
	t_player		one;
	t_img			img;
	t_prm_pkg		pkg;

	one = ft_preset_player(&cfg);
	img = ft_preset_img(&cfg);
	pkg = ft_pkg_param(&cfg, &img, &one);
	ft_raycast((void *)&pkg);
	mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);
	mlx_hook(img.win_ptr, 2, 1, ft_move_player, &pkg);
//	mlx_loop_hook(img.mlx_ptr, ft_raycast, &pkg);
	mlx_loop(img.mlx_ptr);
	mlx_destroy_image(img.mlx_ptr, img.img_ptr);
	mlx_destroy_window(img.mlx_ptr, img.win_ptr);
	free(img.mlx_ptr);
}

int		main(int ac, char **av)
{

	t_file_data		fdata;
	t_config		setup_cfg;

	fdata = ft_preset_fdata(ac, av);
	setup_cfg = ft_get_config(&fdata);
	ft_add_map(&setup_cfg, &fdata);
	ft_launch_game(setup_cfg);
	ft_print_cfg(&setup_cfg);
	ft_wipe_cfg(&setup_cfg);
	ft_wipe_file_data(&fdata);
	return (0);
}
