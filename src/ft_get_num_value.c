/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_num_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 07:30:55 by iguidado          #+#    #+#             */
/*   Updated: 2022/09/26 00:37:10 by lescribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_color(t_config *cfg, t_file_data *fdata, int flag)
{
	if (cfg->mask & flag)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	if (!ft_str_is_colorcode(fdata->paramlist[1]))
		ft_manage_parse_error(ERROR_LEXICAL, cfg, fdata);
}

int	ft_get_ceilar(t_config *cfg, t_file_data *fdata)
{
	int	i;
	int	nbr;

	ft_check_color(cfg, fdata, FLAG_CEIL);
	i = 0;
	cfg->ceilar_color = 0;
	while (fdata->paramlist[1][i])
	{
		nbr = 0;
		while (ft_isdigit(fdata->paramlist[1][i]))
		{
			nbr = (nbr * 10) + (fdata->paramlist[1][i] - '0');
			i++;
		}
		cfg->ceilar_color = (cfg->ceilar_color << 8) + nbr;
		if (fdata->paramlist[1][i] == ',')
			i++;
	}
	return (FLAG_CEIL);
}

int	ft_get_floor(t_config *cfg, t_file_data *fdata)
{
	int	i;
	int	nbr;

	ft_check_color(cfg, fdata, FLAG_FLOOR);
	i = 0;
	cfg->floor_color = 0;
	while (fdata->paramlist[1][i])
	{
		nbr = 0;
		while (ft_isdigit(fdata->paramlist[1][i]))
		{
			nbr = (nbr * 10) + (fdata->paramlist[1][i] - '0');
			i++;
		}
		if (nbr > 255)
			ft_manage_parse_error(ERROR_LEXICAL, cfg, fdata);
		cfg->floor_color = (cfg->floor_color << 8) + nbr;
		if (fdata->paramlist[1][i])
			i++;
	}
	return (FLAG_FLOOR);
}
