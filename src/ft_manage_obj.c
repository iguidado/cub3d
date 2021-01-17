/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:55:13 by iguidado          #+#    #+#             */
/*   Updated: 2021/01/17 16:56:27 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_manage_obj(t_prm_pkg *pkg)
{
	t_pos_lst	*obj_lst;
	t_obj		obj;
	int			spri_x;

	obj_lst = pkg->obj_lst;
	while (obj_lst)
	{
		if (ft_is_inscrn(pkg->cfg, pkg->one, obj_lst->pos, &obj))
		{
			ft_complete_obj(pkg->cfg, pkg->img, &obj);
			spri_x = 0;
			while (spri_x < obj.width)
			{
				ft_paint_spri_x(spri_x, pkg, &obj);
				spri_x++;
			}
		}
		obj_lst = obj_lst->next;
	}
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

void	ft_spri_pix(t_img *img, int *screen, t_spri_coord *spri, int ceil)
{
	int y;
	int pix_x;
	int	pix_y;
	int *spri_text;

	pix_x = (int)(spri->sample_x * img->spri_text.width);
	pix_y = (int)(spri->sample_y * img->spri_text.width)
		* img->spri_text.width;
	y = (int)(spri->ly + ceil) * img->img_width;
	spri_text = ((int *)img->spri_text.data);
	if (spri_text[pix_x + pix_y])
	{
		screen[(spri->screen_x + y)] = spri_text[pix_x + pix_y];
	}
}

void	ft_complete_obj(t_config *cfg, t_img *img, t_obj *obj)
{
	obj->floor = cfg->screen_height - obj->ceiling;
	obj->height = obj->floor - obj->ceiling;
	obj->a_ratio = (float)img->spri_text.height / (float)img->spri_text.width;
	obj->width = obj->height / obj->a_ratio;
	obj->middle = (0.5f * (obj->angle / (FOV / 2.0f)) + 0.5f)
		* (float)cfg->screen_width;
}

void	ft_paint_spri_x(int	spri_x, t_prm_pkg *pkg, t_obj *obj)
{
	t_spri_coord	spri;
	int				*screen;

	screen = (int *)pkg->img->img_data;
	spri.lx = spri_x;
	spri.sample_x = spri.lx / obj->width;
	spri.screen_x = (int)(obj->middle + spri.lx - (obj->width / 2.0f));
	if (spri.screen_x < 0 || (spri.screen_x >= pkg->cfg->screen_width))
		return ;
	if (pkg->z_buffer[spri.screen_x] <= obj->dist)
		return ;
	pkg->z_buffer[spri.screen_x] = obj->dist;
	spri.ly = 0;
	while (++spri.ly < obj->height)
	{
		spri.sample_y = spri.ly / obj->height;
		if (spri.ly + obj->ceiling >= 0
				&& spri.ly + obj->ceiling < pkg->cfg->screen_width)
			ft_spri_pix(pkg->img, screen, &spri, obj->ceiling);
	}
}

void	ft_paint_obj(t_prm_pkg *pkg, t_obj *obj)
{
	int				spri_x;

}
