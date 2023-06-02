/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:43:50 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/22 18:30:07 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_text	ft_load_text(t_img *img, char *text_name)
{
	t_text	new;
	int		endian;
	int		bpp;
	int		line_size;

	new.ptr = mlx_xpm_file_to_image(img->mlx_ptr, text_name,
			&new.width, &new.height);
	if (!new.ptr)
		return (new);
	new.data = mlx_get_data_addr(new.ptr, &bpp, &line_size, &endian);
	return (new);
}

void	ft_setup_text(t_config *cfg, t_img *img)
{
	int		dum;

	img->img_ptr = mlx_new_image(img->mlx_ptr, cfg->screen_width,
			cfg->screen_height);
	if (!img->img_ptr)
		ft_wipe_run(cfg, img);
	img->img_width = cfg->screen_width;
	img->img_height = cfg->screen_height;
	img->img_data = mlx_get_data_addr(img->img_ptr, &dum, &dum, &dum);
	img->no_text = ft_load_text(img, cfg->no_text);
	if (!img->no_text.ptr)
		ft_wipe_run(cfg, img);
	img->so_text = ft_load_text(img, cfg->so_text);
	if (!img->no_text.ptr)
		ft_wipe_run(cfg, img);
	img->ea_text = ft_load_text(img, cfg->ea_text);
	if (!img->no_text.ptr)
		ft_wipe_run(cfg, img);
	img->we_text = ft_load_text(img, cfg->we_text);
	if (!img->no_text.ptr)
		ft_wipe_run(cfg, img);
}
