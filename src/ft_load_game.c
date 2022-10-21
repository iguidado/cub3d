/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:43:50 by iguidado          #+#    #+#             */
/*   Updated: 2022/09/26 03:01:52 by lescribe         ###   ########.fr       */
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
	new.data = mlx_get_data_addr(new.ptr, &bpp, &line_size, &endian);
	printf("load %s : width = %i height = %i\n",
		text_name, new.width, new.height);
	return (new);
}
