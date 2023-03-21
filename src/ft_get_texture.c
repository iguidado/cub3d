/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 07:31:27 by iguidado          #+#    #+#             */
/*   Updated: 2023/03/21 08:22:37 by iguidado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_no_text(t_config *cfg, t_file_data *fdata)
{
	int	tmp_fd;

	if (cfg->mask & FLAG_NO)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	tmp_fd = open(fdata->paramlist[1], O_RDONLY);
	if ((tmp_fd) < 0)
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	close(tmp_fd);
	if (!ft_isxpm(fdata->paramlist[1]))
		ft_manage_parse_error(ERROR_XPM, cfg, fdata);
	cfg->no_text = ft_strdup(fdata->paramlist[1]);
	return (FLAG_NO);
}

int	ft_get_so_text(t_config *cfg, t_file_data *fdata)
{
	int	tmp_fd;

	if (cfg->mask & FLAG_SO)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	tmp_fd = open(fdata->paramlist[1], O_RDONLY);
	if ((tmp_fd) < 0)
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	close(tmp_fd);
	if (!ft_isxpm(fdata->paramlist[1]))
		ft_manage_parse_error(ERROR_XPM, cfg, fdata);
	cfg->so_text = ft_strdup(fdata->paramlist[1]);
	return (FLAG_SO);
}

int	ft_get_we_text(t_config *cfg, t_file_data *fdata)
{
	int	tmp_fd;

	if (cfg->mask & FLAG_WE)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	tmp_fd = open(fdata->paramlist[1], O_RDONLY);
	if ((tmp_fd) < 0)
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	close(tmp_fd);
	if (!ft_isxpm(fdata->paramlist[1]))
		ft_manage_parse_error(ERROR_XPM, cfg, fdata);
	cfg->we_text = ft_strdup(fdata->paramlist[1]);
	return (FLAG_WE);
}

int	ft_get_ea_text(t_config *cfg, t_file_data *fdata)
{
	int	tmp_fd;

	if (cfg->mask & FLAG_EA)
		ft_manage_parse_error(ERROR_DUPLICATE, cfg, fdata);
	if (ft_count_param(fdata->paramlist) != 2)
		ft_manage_parse_error(ERROR_SYNTAX, cfg, fdata);
	tmp_fd = open(fdata->paramlist[1], O_RDONLY);
	if ((tmp_fd) < 0)
		ft_manage_parse_error(ERROR_SYSCALL, cfg, fdata);
	close(tmp_fd);
	if (!ft_isxpm(fdata->paramlist[1]))
		ft_manage_parse_error(ERROR_XPM, cfg, fdata);
	cfg->ea_text = ft_strdup(fdata->paramlist[1]);
	return (FLAG_EA);
}
