/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:52:36 by iguidado          #+#    #+#             */
/*   Updated: 2020/05/12 03:32:16 by iguidado         ###   ########.fr       */
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

int		ft_is_oob(char **map, float x, float y)
{
	int i;
	int j;

	if (x < 0.0f || y < 0.0f)
		return (1);
	i = 0;
	j = 0;
	while (map[i] && i < (int)y )
		i++;
	if (!map[i])
		return (1);
	while (map[i][j] && j < (int)x)
		j++;
	if (!map[i][j])
		return (1);
	return (0);
}

void	ft_fill_height(t_prm_pkg *cub, t_ray_x *ray, t_block *block)
{
	int	i;
	int	*screen;
	int	ceil;
	int	floor;
	float	sample_y;

	screen = (int *)cub->img->img_data;
	ceil = (cub->cfg->screen_height / 2.0f);
	ceil -= cub->cfg->screen_height / ((float)ray->len);
	floor = cub->cfg->screen_height - ceil;
	i = ray->x;
	while (i < (cub->cfg->screen_height * cub->cfg->screen_width))
	{
		if (i < (ceil * cub->cfg->screen_width))
			screen[i] = cub->cfg->ceilar_color;
		else if (i < (floor * cub->cfg->screen_width))
		{
			sample_y = ft_get_sample_y(i, cub->cfg->screen_width, ceil, floor);
			screen[i] = ft_get_wall_pixel(sample_y, block);
		}
		else if (i < (cub->cfg->screen_height * cub->cfg->screen_width))
			screen[i] = cub->cfg->floor_color;
		i += cub->cfg->screen_width;
	}
}

void	ft_fill_height_void(t_config *cfg, t_img *img, t_ray_x *ray)
{
	int	i;
	int	*screen;
	int	ceil;
	int	floor;

	screen = (int *)img->img_data;
	ceil = (cfg->screen_height / 2.0f);
	ceil -= cfg->screen_height / ((float)ray->len);
	floor = cfg->screen_height - ceil;
	i = ray->x;
	while (i < (cfg->screen_height * cfg->screen_width))
	{
		if (i < (ceil * cfg->screen_width))
			screen[i] = cfg->ceilar_color;
		else if (i < (floor * cfg->screen_width))
			screen[i] = 0;
		else if (i < (cfg->screen_height * cfg->screen_width))
			screen[i] = cfg->floor_color;
		i += cfg->screen_width;
	}
}

void		ft_set_ray(t_prm_pkg *cub, t_ray_x *ray)
{
	float	leftmost_ray;
	float	x_normalized;

	leftmost_ray = (cub->one->angle - cub->one->fov / 2.0f);
	x_normalized = ((float)ray->x / (float)cub->cfg->screen_width);
	ray->angle =  leftmost_ray + x_normalized * cub->one->fov;
	ray->eye_x = sin(ray->angle);
	ray->eye_y = cos(ray->angle);
	ray->len = 0.0f;
}

int		ft_raycast(t_prm_pkg *cub, t_ray_x *ray)
{
	while (1)
	{
		ray->len += 0.01f;
		ray->test_x = (int)(cub->one->x + ray->eye_x * ray->len);
		ray->test_y = (int)(cub->one->y + ray->eye_y * ray->len);
		if (ft_is_oob(cub->cfg->map, (float)ray->test_x, (float)ray->test_y))
		{
			ray->len -= 0.01f;
			ray->test_x = (int)(cub->one->x + ray->eye_x * ray->len);
			ray->test_y = (int)(cub->one->y + ray->eye_y * ray->len);
			return (0);
		}
		if (cub->cfg->map[ray->test_y][ray->test_x] == '1')
			return (1);
	}
}

void		ft_raycasting(t_prm_pkg *cub)
{
	t_ray_x		ray;
	t_block		block;

	ray.x = 0;
	while (ray.x < cub->cfg->screen_width)
	{
		ft_set_ray(cub, &ray);
		if (!ft_raycast(cub, &ray))
			ft_fill_height_void(cub->cfg, cub->img, &ray);
		else
		{
			block = ft_get_block(cub->cfg, &ray, cub->one);
			ft_add_wall_to_block(cub->img, &block);
			ft_fill_height(cub, &ray, &block);
		}
		ray.x++;
	}
}

int		ft_obj_is_inscreen(t_config *cfg, t_player *one, t_fdot pos, t_obj *obj)
{
	float	vec_x;
	float	vec_y;
	float	dir_x;
	float	dir_y;
	float	dist;

	vec_x = pos.x - one->x;
	vec_y = pos.y - one->y;
	dist = sqrtf(vec_x * vec_x + vec_y * vec_y);
	dir_x = sin(one->angle);
	dir_y = cos(one->angle);
	obj->angle = atan2f(dir_y, dir_x) - atan2f(vec_y, vec_x);
	if (obj->angle < -M_PI)
		obj->angle += 2.0f * M_PI;
	if (obj->angle > M_PI)
		obj->angle -= 2.0f * M_PI;
	if (dist > 0.5f && (fabs(obj->angle) < one->fov / 2.0f))
	{
		obj->ceiling = (float)(cfg->screen_height / 2.0f)
			- (cfg->screen_height / dist);
		return (1);
	}
	return (0);
}

void	ft_complete_obj(t_config *cfg, t_img *img, t_obj *obj)
{
	obj->floor = cfg->screen_height - obj->ceiling;
	obj->height = obj->floor - obj->ceiling;
	obj->a_ratio = (float)img->spri_text.height / (float)img->spri_text.width;
	obj->width = obj->height / obj->a_ratio;
	obj->middle = (0.5f * (obj->angle / (FOV / 2.0f)) + 0.5f) * (float)cfg->screen_width;
}

void	ft_paint_obj(t_prm_pkg *pkg, t_obj *obj)
{
	float	ly;
	float	lx;
	float	sample_y;
	float	sample_x;
	int		screen_x;
	int		*screen;

	ft_complete_obj(pkg->cfg, pkg->img, obj);
	lx = -1;
	while (++lx < obj->width)
	{
		ly = -1;
		while (++ly < obj->height)
		{
			sample_x = lx / obj->width;
			sample_y = ly / obj->height;
			screen_x = (int)(obj->middle + lx - (obj->width / 2.0f));
			if (screen_x >= 0 && screen_x < pkg->cfg->screen_width
				&& ly + obj->ceiling >= 0 && ly +obj->ceiling < pkg->cfg->screen_width)
			{
				screen = (int *)pkg->img->img_data;
				screen[(screen_x + (int)(ly + obj->ceiling) * pkg->cfg->screen_width)]
					= ((int *)pkg->img->spri_text.data)
					[(int)(sample_x * pkg->img->spri_text.width)
					+ ((int)(sample_y * pkg->img->spri_text.height)
							* pkg->img->spri_text.height)];
			}
		}
	}
}

void	ft_manage_obj(t_prm_pkg *pkg)
{
	t_pos_lst	*obj_lst;
	t_obj		tmp_obj;

	obj_lst = pkg->obj_lst;
	while (obj_lst)
	{
		if (ft_obj_is_inscreen(pkg->cfg, pkg->one, obj_lst->pos, &tmp_obj))
			ft_paint_obj(pkg, &tmp_obj);
		obj_lst = obj_lst->next;
	}
}

int		ft_render_screen(void *param)
{
	t_prm_pkg *pkg;

	pkg = (t_prm_pkg *)param;
	ft_raycasting(pkg);
	ft_manage_obj(pkg);
	mlx_put_image_to_window(pkg->img->mlx_ptr, pkg->img->win_ptr, pkg->img->img_ptr, 0, 0);
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
	else if (keycode == KEY_RIGHT)
	{
		ft_putnbr(keycode);
		ft_putchar('\n');
		cub->one->angle -= 0.1f;
	}
	ft_move_player(keycode, cub);
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
	//	ft_raycast((void *)&pkg);
	//	mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);
	mlx_hook(img.win_ptr, 2, 1, ft_get_key, &pkg);
	mlx_loop_hook(img.mlx_ptr, ft_render_screen, &pkg);
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
	ft_print_obj(setup_cfg.obj_list);
	ft_launch_game(setup_cfg);
	ft_print_fdata(&fdata);
	ft_print_cfg(&setup_cfg);
	ft_wipe_cfg(&setup_cfg);
	ft_wipe_file_data(&fdata);
	return (0);
}
