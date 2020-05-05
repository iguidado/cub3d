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

char	*wrap_mlx_get_addr_data(void *img_ptr)
{
	int bpp;
	int line_size;
	int endian;
	char	*img_data;

	img_data = mlx_get_data_addr(img_ptr, &bpp, &line_size, &endian);
//	printf("\n[%i]\n", line_size);
	return (img_data);
}

/*
**	int	ft_get_wall_pixel(t_block *block, int sample_y)
**	{
**	
**		return ();
**	}
*/

void	ft_fill_height(t_config *cfg, t_img *img, t_ray_x *ray, t_block *block)
{
	int	i;
	int	*screen;
	int	ceiling;
	int	floor;
	float	sample_y;

	screen = (int *)img->img_data;
	ceiling = (cfg->screen_height / 2.0f) - cfg->screen_height / ((float)ray->len);
	floor = cfg->screen_height - ceiling;
	i = ray->x;
	while (i < (cfg->screen_height * cfg->screen_width))
	{
		if (i < (ceiling * cfg->screen_width))
			screen[i] = cfg->ceilar_color;
		else if (i < (floor * cfg->screen_width))
		{
	//	printf("trying to get pixel for wall\t");
		sample_y = (((float)(i / cfg->screen_width) - (float)ceiling) / ((float)floor - (float)ceiling));
//		printf("at  sample x = [%3f],  y = [%3f]\n", block->sample_x, sample_y);
	screen[i] = ((int *)block->wall_text->data)[((int)(block->sample_x * block->wall_text->width) + (int)(sample_y * block->wall_text->height) * block->wall_text->width)];
	//	printf("Got Pixel at x = [%i], y = [%i]\n", (int)(block->sample_x * block->wall_text->width), (int)(sample_y * block->wall_text->height));
		}
		else if (i < (cfg->screen_height * cfg->screen_width))
		{
		//	printf("getting pixel for floor\n");
			screen[i] = cfg->floor_color;
		}
		i += cfg->screen_width;
	}
}

int		ft_is_oob(char **map, float x, float y)
{
	int i;
	int j;

	if (x < 0.0f || y < 0.0f)
		return (1);
	i = 0;
	j = 0;
	while (i < (int)y && map[i])
		i++;
	if (!map[i])
		return (1);
	while (j < (int)x && map[i][j])
		j++;
	if (!map[i][j])
		return (1);
	return (0);
}

void		ft_escape_game(void *param)
{
	exit(EXIT_SUCCESS);
}

void		ft_exit_game(void *param)
{
	exit(EXIT_FAILURE);
}

void		ft_add_wall_to_block(t_img *img, t_block *block)
{
	if (block->test_angle >= -M_PI * 0.25f && block->test_angle < M_PI * 0.25)
	{
		block->wall_text = &img->we_text;
		block->sample_x = block->hitpoint.y - (float)block->pos.y;
	}
	if (block->test_angle >= M_PI * 0.25f && block->test_angle < M_PI * 0.75)
	{
		block->wall_text = &img->so_text;
		block->sample_x = 1.0f - (block->hitpoint.x - (float)block->pos.x);
	}
	if (block->test_angle < -M_PI * 0.25f && block->test_angle >= -M_PI * 0.75)
	{
		block->wall_text = &img->no_text;
		block->sample_x = block->hitpoint.x - (float)block->pos.x;
	}
	if (block->test_angle >= M_PI * 0.75f || block->test_angle < -M_PI * 0.75)
	{
		block->wall_text = &img->ea_text;
		block->sample_x = 1.0f - (block->hitpoint.y - (float)block->pos.y);
	}
}

t_block		ft_get_block(t_config *cfg, t_ray_x *ray, t_player *one)
{
	t_block	block;

	block.pos.x = ray->test_x;
	block.pos.y = ray->test_y;
	block.hitpoint.x = (one->x + ray->eye_x * ray->len);
	block.hitpoint.y = (one->y + ray->eye_y * ray->len);
	block.midpoint.x = (float)ray->test_x + 0.5f;
	block.midpoint.y = (float)ray->test_y + 0.5f;
	block.test_angle = atan2f(block.hitpoint.y - block.midpoint.y,
				block.hitpoint.x - block.midpoint.x);
	return (block);
}

int		ft_raycast(void *param)
{
	t_ray_x		ray;
	t_prm_pkg	*cub;
	t_block		block;
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
/*
**		if (ft_is_oob(cub->cfg->map, (float)ray.test_x, (float)ray.test_y))
**		{
**			wall_hitted--;
**			ray.len -= 1.0f;
**			ray.test_x = (int)(cub->one->x + ray.eye_x * ray.len);
**			ray.test_y = (int)(cub->one->y + ray.eye_y * ray.len);
**		}
*/
			if (cub->cfg->map[ray.test_y][ray.test_x] == '1')
			{
				wall_hitted++;
				block = ft_get_block(cub->cfg, &ray, cub->one);
				ft_add_wall_to_block(cub->img, &block);
			}
		}
	//	printf("block tested, %3i, %3i\n", ray.test_x, ray.test_y);
		ft_fill_height(cub->cfg, cub->img, &ray, &block);
		ray.x++;
	}
//	printf("Putting Image on Window\n");
	mlx_put_image_to_window(cub->img->mlx_ptr, cub->img->win_ptr, cub->img->img_ptr, 0, 0);
	return (0);
}

void		ft_move_player(int keycode, t_prm_pkg *cub)
{
	float new_x;
	float new_y;

	new_x = -1.0f;
	new_y = -1.0f;
	if (keycode == KEY_W)
	{
		new_y = cub->one->y + cos(cub->one->angle) * 0.1f;
		new_x = cub->one->x + sin(cub->one->angle) * 0.1f;
	}
	else if (keycode == KEY_A)
	{
		new_x = cub->one->x - cos(cub->one->angle) * 0.1f;
		new_y = cub->one->y + sin(cub->one->angle) * 0.1f;
	}
	else if (keycode == KEY_S)
	{
		new_y = cub->one->y - cos(cub->one->angle) * 0.1f;
		new_x = cub->one->x - sin(cub->one->angle) * 0.1f;
	}
	else if (keycode == KEY_D)
	{
		new_x = cub->one->x + cos(cub->one->angle) * 0.1f;
		new_y = cub->one->y - sin(cub->one->angle) * 0.1f;
	}
	if (new_x > -1.0f)
	{
		    cub->one->x = new_x;
		    cub->one->y = new_y;
	}
}

int		ft_get_key(int keycode, void *param)
{
	t_prm_pkg *cub;

	cub = (t_prm_pkg *)param;
	if (keycode == KEY_LEFT)
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
		cub->one->angle += 0.1f;
	}
	if (keycode == KEY_RIGHT)
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
		cub->one->angle -= 0.1f;
	}
	ft_move_player(keycode, cub);
//	printf("%3f, %3f\n", cub->one->x, cub->one->y);
	ft_raycast(param);
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
//	ft_raycast((void *)&pkg);
//	mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);
	mlx_hook(img.win_ptr, 2, 1, ft_get_key, &pkg);
	mlx_loop_hook(img.mlx_ptr, ft_raycast, &pkg);
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
