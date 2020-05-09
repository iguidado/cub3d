/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:41:47 by iguidado          #+#    #+#             */
/*   Updated: 2020/05/09 18:47:52 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		ft_get_sample_y(int i, int scrn_width, int ceiling, int floor)
{
	float y;
	float wall_y;
	float sample_y;

	y = (float)(i / scrn_width);
	wall_y = y - (float)ceiling;
	sample_y = wall_y / ((float)floor - (float)ceiling);
	return (sample_y);
}

int			ft_get_wall_pixel(float sample_y, t_block *block)
{
	int	pixel_color;
	int	*wall_sprite;
	int	wall_x;
	int	wall_y;

	wall_sprite = (int *)block->wall_text->data;
	wall_x = (int)(block->sample_x * block->wall_text->width);
	wall_y = (int)(sample_y * block->wall_text->height);
	pixel_color = wall_sprite[wall_x + wall_y * block->wall_text->width];
	return (pixel_color);
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
	block.hitpoint.y = (one->y + ray->eye_y * ray->len);
	block.midpoint.x = (float)ray->test_x + 0.5f;
	block.midpoint.y = (float)ray->test_y + 0.5f;
	block.test_angle = atan2f(block.hitpoint.y - block.midpoint.y,
				block.hitpoint.x - block.midpoint.x);
	return (block);
}
