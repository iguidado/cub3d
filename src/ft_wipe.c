/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <iguidado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 01:48:21 by iguidado          #+#    #+#             */
/*   Updated: 2020/04/29 01:48:24 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (cfg->map)
		ft_free_tab(&cfg->map);
	cfg->no_text = NULL;
	cfg->ea_text = NULL;
	cfg->so_text = NULL;
	cfg->we_text = NULL;
	cfg->spri_text = NULL;
	cfg->map = NULL;
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
