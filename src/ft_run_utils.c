/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 19:24:53 by iguidado          #+#    #+#             */
/*   Updated: 2020/07/17 19:24:54 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_is_oob(t_map *map, float x, float y)
{
	if (x < 0.0f || y < 0.0f)
		return (1);
	if (((int)x) >= map->res.x || ((int)y) >= map->res.y)
		return (1);
	return (0);
}

int		ft_is_inscrn(t_config *cfg, t_player *one, t_fdot pos, t_obj *obj)
{
	float	vec_x;
	float	vec_y;
	float	dir_x;
	float	dir_y;

	vec_x = pos.x - one->x;
	vec_y = pos.y - one->y;
	obj->dist = sqrtf(vec_x * vec_x + vec_y * vec_y);
	dir_x = sin(one->angle);
	dir_y = cos(one->angle);
	obj->angle = atan2f(dir_y, dir_x) - atan2f(vec_y, vec_x);
	if (obj->angle < -M_PI)
		obj->angle += 2.0f * M_PI;
	if (obj->angle > M_PI)
		obj->angle -= 2.0f * M_PI;
	if (obj->dist > 0.5f && (fabs(obj->angle) < one->fov / 2.0f))
	{
		obj->ceiling = (float)(cfg->screen_height / 2.0f)
			- (cfg->screen_height / obj->dist);
		return (1);
	}
	return (0);
}
