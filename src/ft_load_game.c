/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:43:50 by iguidado          #+#    #+#             */
/*   Updated: 2020/05/09 18:46:40 by iguidado         ###   ########.fr       */
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
		current_node = (t_pos_lst *)malloc(sizeof(t_pos_lst));
		current_node->pos.x = (float)obj_list->pos.x + 0.5f;
		current_node->pos.y = (float)obj_list->pos.y + 0.5f;
		current_node->next = new_list;
		new_list = current_node;
		obj_list = obj_list->next;
	}
	return (new_list);
}

t_text		ft_load_text(t_img *img, char *text_name)
{
	t_text	new;
	int		endian;
	int		bpp;
	int		line_size;

	new.ptr = mlx_xpm_file_to_image(img->mlx_ptr, text_name
			, &new.width, &new.height);
	new.data = mlx_get_data_addr(new.ptr, &bpp, &line_size, &endian);
	printf("load %s : width = %i height = %i\n"
			, text_name, new.width, new.height);
	return (new);
}
