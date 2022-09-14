/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 23:27:14 by iguidado          #+#    #+#             */
/*   Updated: 2022/09/14 15:32:34 by lescribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_get_input(int keycode, void *param)
{
	int			i;
	t_prm_pkg	*pkg;

	pkg = (t_prm_pkg *)param;
	i = 0;
	while (i < NB_INPUT)
	{
		if (pkg->one->key_id[i] == keycode)
			pkg->one->input[i] = true;
		i++;
	}
	return (0);
}

int			ft_release_input(int keycode, void *param)
{
	int			i;
	t_prm_pkg	*pkg;

	pkg = (t_prm_pkg *)param;
	i = 0;
	while (i < NB_INPUT)
	{
		if (pkg->one->key_id[i] == keycode)
			pkg->one->input[i] = false;
		i++;
	}
	return (0);
}

void		ft_move_player(t_player *one)
{
	if (one->input[INPUT_LEFT])
		one->angle += 0.1f;
	if (one->input[INPUT_RIGHT])
		one->angle -= 0.1f;
	if (one->input[INPUT_W])
	{
		one->x += sin(one->angle) * one->speed;
		one->y += cos(one->angle) * one->speed;
	}
	if (one->input[INPUT_A])
	{
		one->x -= cos(one->angle) * one->speed;
		one->y += sin(one->angle) * one->speed;
	}
	if (one->input[INPUT_S])
	{
		one->x -= sin(one->angle) * one->speed;
		one->y -= cos(one->angle) * one->speed;
	}
	if (one->input[INPUT_D])
	{
		one->x += cos(one->angle) * one->speed;
		one->y -= sin(one->angle) * one->speed;
	}
}

void		ft_escape_game(t_prm_pkg *cub)
{
	ft_putendl("escaping game");
	free(cub->z_buffer);
	ft_wipe_cfg(cub->cfg);
//	ft_wipe_obj(&cub->obj_lst);
	ft_wipe_img(cub->img);
	exit(EXIT_SUCCESS);
}

int			ft_prep_escape(t_prm_pkg *pkg)
{
	pkg->one->input[INPUT_ESC] = true;
	return (0);
}
