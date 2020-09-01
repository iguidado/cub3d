/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:43:50 by iguidado          #+#    #+#             */
/*   Updated: 2020/08/28 01:06:25 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pos_lst	*ft_load_obj(t_obj_spwn *obj_list)
{
	t_pos_lst *new_list;
	t_pos_lst *current_node;

	if (!obj_list)
		return (NULL);
	new_list = NULL;
	while (obj_list)
	{
		if (!(current_node = (t_pos_lst *)malloc(sizeof(t_pos_lst))))
		{
			ft_wipe_obj(&new_list);
			return (NULL);
		}
		current_node->pos.x = (float)obj_list->pos.x + 0.5f;
		current_node->pos.y = (float)obj_list->pos.y + 0.5f;
		current_node->next = new_list;
		new_list = current_node;
		obj_list = obj_list->next;
	}
	return (new_list);
}

int			ft_load_text(t_text *text, t_img *img, char *text_name)
{
	int		endian;
	int		bpp;
	int		line_size;

	if (!(text->ptr = mlx_xpm_file_to_image(img->mlx_ptr, text_name
			, &text->width, &text->height)))
		return (0);
	text->data = mlx_get_data_addr(text->ptr, &bpp, &line_size, &endian);
	return (1);
}

int			ft_load_all_text(t_img *new, t_config *cfg)
{
	if (!ft_load_text(&new->no_text, new, cfg->no_text) ||
			!ft_load_text(&new->so_text, new, cfg->so_text) ||
			!ft_load_text(&new->ea_text, new, cfg->ea_text) ||
			!ft_load_text(&new->we_text, new, cfg->we_text) ||
			!ft_load_text(&new->spri_text, new, cfg->spri_text))
		return (0);
	return (1);
}
