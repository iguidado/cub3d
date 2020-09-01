/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:55:13 by iguidado          #+#    #+#             */
/*   Updated: 2020/08/28 00:49:49 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_complete_obj(t_config *cfg, t_img *img, t_obj *obj)
{
	obj->floor = cfg->screen_height - obj->ceiling;
	obj->height = obj->floor - obj->ceiling;
	obj->a_ratio = (float)img->spri_text.height / (float)img->spri_text.width;
	obj->width = obj->height / obj->a_ratio;
	obj->middle = (0.5f * (obj->angle / (FOV / 2.0f)) + 0.5f)
		* (float)cfg->screen_width;
}

void	ft_spri_pix(t_img *img, int *screen, t_spri_coord *spri, int ceil)
{
	int y;
	int pix_x;
	int	pix_y;
	int *spri_text;

	pix_x = (int)(spri->sample_x * img->spri_text.width);
	pix_y = (int)(spri->sample_y * img->spri_text.height)
		* img->spri_text.height;
	y = (int)(spri->ly + ceil) * img->img_width;
	spri_text = ((int *)img->spri_text.data);
	if (spri_text[pix_x + pix_y])
	{
		screen[(spri->screen_x + y)] = spri_text[pix_x + pix_y];
	}
}

void	ft_set_spri_col(t_spri_coord *spri, t_obj *obj, t_prm_pkg *pkg)
{
	int				*screen;

	screen = (int *)pkg->img->img_data;
	spri->ly = -1;
	spri->sample_x = spri->lx / obj->width;
	spri->screen_x = (int)(obj->middle + spri->lx - (obj->width / 2.0f));
	if (spri->screen_x >= 0
			&& spri->screen_x < pkg->cfg->screen_width)
	{
		if (pkg->z_buffer[spri->screen_x] > obj->dist)
		{
			pkg->z_buffer[spri->screen_x] = obj->dist;
			while (++spri->ly < obj->height)
			{
				spri->sample_y = spri->ly / obj->height;
				if (spri->ly + obj->ceiling >= 0
						&& spri->screen_x < pkg->cfg->screen_width
						&& spri->ly + obj->ceiling < pkg->cfg->screen_width)
					ft_spri_pix(pkg->img, screen, spri, obj->ceiling);
			}
		}
	}
}

void	ft_paint_obj(t_prm_pkg *pkg, t_obj *obj)
{
	t_spri_coord	spri;

	ft_complete_obj(pkg->cfg, pkg->img, obj);
	spri.lx = -1;
	while (++spri.lx < obj->width)
	{
		ft_set_spri_col(&spri, obj, pkg);
	}
}

void	ft_manage_obj(t_prm_pkg *pkg)
{
	t_pos_lst	*obj_lst;
	t_obj		tmp_obj;

	obj_lst = pkg->obj_lst;
	while (obj_lst)
	{
		if (ft_is_inscrn(pkg->cfg, pkg->one, obj_lst->pos, &tmp_obj))
			ft_paint_obj(pkg, &tmp_obj);
		obj_lst = obj_lst->next;
	}
}
