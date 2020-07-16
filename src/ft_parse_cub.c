/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:29:21 by iguidado          #+#    #+#             */
/*   Updated: 2020/07/11 07:29:27 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int			ft_strequ(char *str1, char *str2)
{
	while (*str1 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (!*str1 && !*str2)
		return (1);
	return (0);
}

int			ft_str_beginby(char *str, char *tofind)
{
	while (*str && *str == *tofind)
	{
		str++;
		tofind++;
	}
	if (!*tofind)
		return (1);
	return (0);
}

int			ft_get_next_param(t_file_data *fdata)
{
	int ret;

	if (fdata->line)
		free(fdata->line);
	if ((ret = get_next_line(fdata->fd, &fdata->line)) == -1)
		return (ERROR_SYSCALL);
	else if (!ret)
		return (ERROR_FILE_END);
	if (ft_line_is_map(fdata->line))
		return (ERROR_MISS_CONF);
	if (ft_line_is_empty(fdata->line))
	{
		free(fdata->line);
		fdata->line = NULL;
		fdata->line_nb++;
		return (ft_get_next_param(fdata));
	}
	fdata->line_nb++;
	return (-1);
}

int			ft_data_to_cfg(t_config *cfg, t_file_data *fdata)
{
	int			i;
	static char id_array[ID_NB][3] =
	{ "R", "C", "F", "NO", "SO", "WE", "EA", "S" };
	static int	(*array_ft[ID_NB])(t_config *, t_file_data *) =
	{ ft_get_res, ft_get_ceilar, ft_get_floor, ft_get_no_text,
		ft_get_so_text, ft_get_we_text, ft_get_ea_text, ft_get_spri_text };

	if (fdata->paramlist)
		ft_free_tab(&fdata->paramlist);
	fdata->paramlist = ft_split(fdata->line, ' ');
	i = 0;
	while (i < ID_NB)
	{
		if (ft_strequ(id_array[i], *fdata->paramlist))
			return (array_ft[i](cfg, fdata));
		i++;
	}
	ft_manage_parse_error(ERROR_ID, cfg, fdata);
	return (-1);
}

t_config	ft_get_config(t_file_data *fdata)
{
	t_config		cfg_new;
	int				error_id;

	cfg_new = ft_preset_config();
	while (cfg_new.mask < 255)
	{
		if ((error_id = ft_get_next_param(fdata)) >= 0)
			ft_manage_parse_error(ERROR_ID, &cfg_new, fdata);
		cfg_new.mask |= ft_data_to_cfg(&cfg_new, fdata);
	}
	return (cfg_new);
}
