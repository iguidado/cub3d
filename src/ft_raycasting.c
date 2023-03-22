/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 02:54:31 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/22 15:19:16 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Simple set ray
**
**	float	leftmost_ray;
**	float	x_normalized;
**	
**	leftmost_ray = (cub->one->angle - cub->one->fov / 2.0f);
**	x_normalized = ((float)ray->x / (float)cub->cfg->screen_width);
**	ray->angle = leftmost_ray + x_normalized * cub->one->fov;
**	ray->eye_x = sin(ray->angle);
**	ray->eye_y = cos(ray->angle);
**	ray->len = 0.0f;
*/

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
	ray->test_x = (int)cub->one->x;
	ray->test_y = (int)cub->one->y;
	if (!ray->eye_x)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->eye_x);
	if (!ray->eye_y)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->eye_y);
}

void	ft_setup_raycast(t_prm_pkg *cub, t_ray_x *ray)
{
	if (ray->eye_x < 0)
	{
		ray->step_x = -1;
		ray->len_x = (cub->one->x - (float)(int)cub->one->x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->len_x = ((float)(int)cub->one->x + 1.0 - cub->one->x) \
			* ray->delta_x;
	}
	if (ray->eye_y < 0)
	{
		ray->step_y = -1;
		ray->len_y = (cub->one->y - (float)(int)cub->one->y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->len_y = ((float)(int)cub->one->y + 1.0 - cub->one->y) \
			* ray->delta_y;
	}
}

int	ft_get_ray_len(t_ray_x	*ray, bool in_map)
{
	if (ray->side == 0)
		ray->len = ray->len_x - ray->delta_x;
	else
		ray->len = ray->len_y - ray->delta_y;
	return (in_map);
}

int	ft_raycast(t_prm_pkg *cub, t_ray_x *ray)
{
	while (1)
	{
		if (ray->len_x < ray->len_y)
		{
			ray->len_x += ray->delta_x;
			ray->test_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->len_y += ray->delta_y;
			ray->test_y += ray->step_y;
			ray->side = 1;
		}
		if (ft_is_oob(&cub->cfg->map, ray->test_x, ray->test_y))
			return (ft_get_ray_len(ray, false));
		if (cub->cfg->map.data[(int)ray->test_y][(int)ray->test_x] == '1')
			return (ft_get_ray_len(ray, true));
	}
}

/*	Simple raycasting
 **
 **	while (1)
 **	{
 **		ray->len += 0.003f;
 **		ray->test_x = (cub->one->x + ray->eye_x * ray->len);
 **		ray->test_y = (cub->one->y + ray->eye_y * ray->len);
 **		if (ft_is_oob(&cub->cfg->map, ray->test_x, ray->test_y))
 **			return (0);
 **		ray->test_x = (int)ray->test_x;
 **		ray->test_y = (int)ray->test_y;
 **		if (cub->cfg->map.data[(int)ray->test_y][(int)ray->test_x] == '1')
 **			return (1);
 **	}
 */

void	ft_raycasting(t_prm_pkg *cub)
{
	t_ray_x		ray;
	t_block		block;
	float		fisheye_fixer;

	ray.x = 0;
	while (ray.x < cub->cfg->screen_width)
	{
		ft_set_ray(cub, &ray);
		ft_setup_raycast(cub, &ray);
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
