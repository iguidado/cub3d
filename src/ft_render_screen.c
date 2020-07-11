/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_screen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 06:13:29 by iguidado          #+#    #+#             */
/*   Updated: 2020/07/11 06:30:35 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	void		ft_set_surround(t_img *img, t_config *cfg)
**	{
**		int *screen;
**		int	i;
**	
**		screen = (int *)img->img_data;
**		i = 0;
**		while (i < cfg->screen_width * cfg->screen_height / 2)
**		{
**			screen[i] = cfg->ceilar_color;
**			i++;
**		}
**		while (i < cfg->screen_width * cfg->screen_height)
**		{
**			screen[i] = cfg->floor_color;
**			i++;
**		}
**	}
**	
*/

void	ft_paint_wall(t_prm_pkg *cub, t_ray_x *ray, t_block *block)
{
	int		i;
	int		*screen;
	int		ceil;
	int		floor;
	float	sample_y;

	screen = (int *)cub->img->img_data;
	ceil = (cub->cfg->screen_height / 2.0f);
	ceil -= cub->cfg->screen_height / ((float)ray->len);
	floor = cub->cfg->screen_height - ceil;
	i = ray->x;
	i += cub->cfg->screen_width * ceil;
	while (i < (floor * cub->cfg->screen_width))
	{
			sample_y = ft_get_sample_y(i, cub->cfg->screen_width, ceil, floor);
			screen[i] = ft_get_wall_pixel(sample_y, block);
			i += cub->cfg->screen_width;
	}
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
	float dy;
	float dx;

	dy = cub->one->y - (float)(int)cub->one->y;
	while (1)
	{
		ray->len += 0.01f;
		ray->test_x = (int)(cub->one->x + ray->eye_x * ray->len);
		ray->test_y = (int)(cub->one->y + ray->eye_y * ray->len);
		if (cub->cfg->map.data[ray->test_y][ray->test_x] == '1')
			return (1);
	}
}

/*
** need to implement DDA algorithm for 
** raycasting
*/
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
		cub->z_buffer[ray.x] = ray.len;
		ray.x++;
	}
}

int		ft_render_screen(void *param)
{
	t_prm_pkg	*pkg;
	t_img		*img;

	pkg = (t_prm_pkg *)param;
	img = pkg->img;
	if (pkg->cfg->mask == 2)
		ft_escape_game(pkg);
//	ft_set_surround(img, pkg->cfg);
	ft_raycasting(pkg);
	ft_manage_obj(pkg);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (0);
}
