/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:52:36 by iguidado          #+#    #+#             */
/*   Updated: 2020/04/29 02:05:42 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	ft_do_img(t_config *cfg, void *mlx_ptr)
{
	t_img	img;
	int		bpp;
	int		linelen;
	int		endian;

	setbuf(stdout, NULL);
	img.img_ptr = mlx_new_image(mlx_ptr, cfg->screen_width, cfg->screen_height);
	img.img_data = mlx_get_data_addr(img.img_ptr, &bpp, &linelen, &endian);
	printf("|bpp = %i|linelen = %i|endian = %i|", bpp, linelen, endian);
	return (img);
}

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

void	ft_raycast(t_config *cfg, t_player *one, t_img *img)
{
	t_ray_x	ray;
	int		wall_hitted;

	ray.x = 0;
	while (ray.x < cfg->screen_width)
	{
		ray.angle = (one->angle - one->fov / 2.0f) + ((float)ray.x / (float)cfg->screen_width) * one->fov;
		ray.eye_x = sin(ray.angle);
		ray.eye_y = cos(ray.angle);
		printf("\t|%3f|%3f|\t", ray.eye_y, ray.eye_x);
		wall_hitted = 0;
		ray.len = 0.0f;
		while (!wall_hitted)
		{
			ray.len += 0.01f;
			ray.test_x = (int)(one->x + ray.eye_x * ray.len);
			ray.test_y = (int)(one->y + ray.eye_y * ray.len);
			if (cfg->map[ray.test_y][ray.test_x] == '1')
				wall_hitted++;
		}
		ft_fill_screen(cfg, img, &ray);
		ray.x++;
	}
}

void	ft_launch_game(t_config cfg)
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		one;
	t_img			img;

	one = ft_preset_player(&cfg);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, cfg.screen_width, cfg.screen_height, "cub3d");
	img = ft_do_img(&cfg, mlx_ptr);
	ft_raycast(&cfg, &one, &img);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img_ptr, 0, 0);
	//mlx_loop(mlx_ptr);
	while (1)
		;
	mlx_destroy_image(mlx_ptr, img.img_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	free(mlx_ptr);
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
