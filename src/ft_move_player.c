/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:43:39 by iguidado          #+#    #+#             */
/*   Updated: 2020/08/28 00:32:52 by iguidado         ###   ########.fr       */
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
