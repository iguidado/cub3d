/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguidado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:23:00 by iguidado          #+#    #+#             */
/*   Updated: 2022/09/14 17:11:25 by lescribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	To Implement give detail about missing
**	configuration line :
**
**	unsigned char	ft_get_finished_process_mask(t_config *cfg)
**	{
**		unsigned char process_mask;
**
**		process_mask = 0;
**		if (cfg->screen_width >= 0 && cfg->screen_height >= 0)
**			process_mask |= FLAG_RES;
**		if (cfg->ceilar_color >= 0)
**			process_mask |= FLAG_CEIL;
**		if (cfg->floor_color >= 0)
**			process_mask |= FLAG_FLOOR;
**		if (cfg->no_text)
**			process_mask |= FLAG_NO;
**		if (cfg->so_text)
**			process_mask |= FLAG_SO;
**		if (cfg->ea_text)
**			process_mask |= FLAG_EA;
**		if (cfg->we_text)
**			process_mask |= FLAG_WE;
**		if (cfg->spri_text)
**			process_mask |= FLAG_SPRI;
**		return (process_mask);
**	}
*/

void	ft_print_error_file(int errnum, t_config *cfg, t_file_data *fdata)
{
	unsigned char	finished_process_mask;

	finished_process_mask = 0;
	if (errnum == ERROR_MISS_CONF)
		ft_putendl_fd(" : missing configuration line", 2);
	if (errnum == ERROR_FILE_END)
		ft_putendl_fd(" : cub file end prematurely", 2);
}

void	ft_print_error_id(int errnum, t_config *cfg, t_file_data *fdata)
{
	char	*tmp;

	tmp = ft_itoa(fdata->line_nb);
	ft_putstr_fd("Line [", 2);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	if (fdata->paramlist)
	{
		ft_putstr_fd("] \"", 2);
		ft_putstr_fd(*fdata->paramlist, 2);
		ft_putchar_fd('\"', 2);
	}
	if (errnum == ERROR_DUPLICATE)
	{
		ft_putendl_fd(" : There is already a configuration with this ID", 2);
	}
	if (errnum == ERROR_ID)
	{
		ft_putendl_fd(" : Can't Reconize this ID", 2);
	}
}

void	ft_print_error_token(int errnum, t_config *cfg, t_file_data *fdata)
{
	char	*tmp;

	tmp = ft_itoa(fdata->line_nb);
	ft_putstr_fd("Line [", 2);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	ft_putstr_fd("] \"", 2);
	ft_putstr_fd(fdata->paramlist[1], 2);
	ft_putchar_fd('\"', 2);
	if (errnum == ERROR_SYNTAX)
		ft_putendl_fd(" : Bad number of argument written", 2);
	else if (errnum == ERROR_LEXICAL)
		ft_putendl_fd(" : Bad type of argument given", 2);
}

void	ft_print_error_map(int errnum, t_config *cfg, t_file_data *fdata)
{
	if (errnum == ERROR_MAP_PLAYER_SPAWN)
	{
		if (cfg->spwn.pos.x == -1)
			ft_putstr_fd("No player spawn specified on the map", 2);
		else
			ft_putstr_fd("More than one player spawn on the map", 2);
	}
	if (errnum == ERROR_MAP_OPEN_BOUNDARIES)
		ft_putstr_fd("Open boundaries surrounding the map", 2);
	if (errnum == ERROR_MAP_EMPTY_LINE)
		ft_putstr_fd("Empty line in middle of map", 2);
	if (errnum == ERROR_MAP_BAD_TILE)
		ft_putstr_fd("Bad tile inside the map", 2);
}

void	ft_manage_parse_error(int errnum, t_config *cfg, t_file_data *fdata)
{
	char			*tmp;
	static void		(*error_ft[])(int, t_config *, t_file_data *)
		= {&ft_print_error_file, &ft_print_error_id,
		&ft_print_error_token, &ft_print_error_map};

	ft_putendl_fd("Error", 2);
	if (errnum == ERROR_SYSCALL)
	{
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (errnum >= ERROR_MAP_PLAYER_SPAWN)
		error_ft[3](errnum, cfg, fdata);
	else
		error_ft[(errnum - 1) / 2](errnum, cfg, fdata);
	ft_wipe_file_data(fdata);
	ft_wipe_cfg(cfg);
	exit(EXIT_FAILURE);
}
