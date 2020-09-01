/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 19:18:34 by iguidado          #+#    #+#             */
/*   Updated: 2020/08/28 00:33:23 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
