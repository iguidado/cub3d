/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:48:21 by iguidado          #+#    #+#             */
/*   Updated: 2022/09/14 15:25:36 by lescribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_wipe_obj_spwn(t_obj_spwn **obj_lst)
{
	t_obj_spwn *next;

	while (*obj_lst)
	{
		next = (*obj_lst)->next;
		free(*obj_lst);
		*obj_lst = next;
	}
}

void	ft_wipe_obj(t_pos_lst **obj_lst)
{
	t_pos_lst *next;

	while (*obj_lst)
	{
		next = (*obj_lst)->next;
		free(*obj_lst);
		*obj_lst = next;
	}
}

void	ft_wipe_cfg(t_config *cfg)
{
	if (cfg->no_text)
		free(cfg->no_text);
	if (cfg->so_text)
		free(cfg->so_text);
	if (cfg->ea_text)
		free(cfg->ea_text);
	if (cfg->we_text)
		free(cfg->we_text);
	if (cfg->spri_text)
		free(cfg->spri_text);
	if (cfg->map.data)
		ft_free_tab(&cfg->map.data);
//	if (cfg->obj_list)
//		ft_wipe_obj_spwn(&cfg->obj_list);
	cfg->no_text = NULL;
	cfg->ea_text = NULL;
	cfg->so_text = NULL;
	cfg->we_text = NULL;
	cfg->spri_text = NULL;
	cfg->map.data = NULL;
	cfg->obj_list = NULL;
}

void	ft_wipe_img(t_img *img)
{
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	mlx_destroy_image(img->mlx_ptr, img->no_text.ptr);
	mlx_destroy_image(img->mlx_ptr, img->so_text.ptr);
	mlx_destroy_image(img->mlx_ptr, img->ea_text.ptr);
	mlx_destroy_image(img->mlx_ptr, img->we_text.ptr);
	mlx_destroy_image(img->mlx_ptr, img->spri_text.ptr);
	mlx_destroy_image(img->mlx_ptr, img->img_ptr);
	free(img->mlx_ptr);
}

void	ft_wipe_file_data(t_file_data *data)
{
	if (data->fd > 2)
	{
		close(data->fd);
		data->fd = -1;
	}
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->paramlist)
	{
		ft_free_tab(&data->paramlist);
		data->paramlist = NULL;
	}
}
