/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 02:54:31 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/18 20:08:15 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_ray(t_prm_pkg *cub, t_ray_x *ray)
{
	float	leftmost_ray;
	float	x_normalized;

	leftmost_ray = (cub->one->angle - cub->one->fov / 2.0f);
	x_normalized = ((float)ray->x / (float)cub->cfg->screen_width);
	ray->angle = leftmost_ray + x_normalized * cub->one->fov;
	ray->eye_x = sin(ray->angle);
	ray->eye_y = cos(ray->angle);
	ray->len = 0.0f;
}

/*
 ** need to implement DDA algorithm for 
 ** raycasting
 */

int	ft_raycast(t_prm_pkg *cub, t_ray_x *ray)
{
	while (1)
	{
		ray->len += 0.001f;
		ray->test_x = (int)(cub->one->x + ray->eye_x * ray->len);
		ray->test_y = (int)(cub->one->y + ray->eye_y * ray->len);
		if (ft_is_oob(&cub->cfg->map, ray->test_x, ray->test_y))
			return (0);
		if (cub->cfg->map.data[(int)ray->test_y][(int)ray->test_x] == '1')
		{
			return (1);
		}
	}
}

void	ft_raycasting(t_prm_pkg *cub)
{
	t_ray_x		ray;
	t_block		block;
	float		fisheye_fixer;

	ray.x = 0;
	while (ray.x < cub->cfg->screen_width)
	{
		ft_set_ray(cub, &ray);
		if (!ft_raycast(cub, &ray))
			ft_fill_height_void(cub->cfg, cub->img, &ray);
		else
		{
			fisheye_fixer = ((float)ray.x / (float)cub->img->img_width
					* cub->one->fov) - cub->one->fov / 2;
			block = ft_get_block(cub->cfg, &ray, cub->one);
			ft_add_wall_to_block(cub->img, &block);
			ray.len *= cos(fisheye_fixer);
			ft_fill_height(cub, &ray, &block);
		}
		cub->z_buffer[ray.x] = ray.len;
		ray.x++;
	}
}
